#ifndef SHORTESTPATHPROBLEM_H
#define SHORTESTPATHPROBLEM_H
#include "graph.h"

#include <map>
#include <limits>
#include <utility>
#include <QDebug>
#include <queue>
#include <deque>
#include <set>

template <class T>
class PreviousWeight
{
public:
   PreviousWeight(int weight, Node<T>* prev = nullptr);
   PreviousWeight();

   inline Node<T>* prev() const {return m_prev;}
   inline int weight() const {return m_weight;}
   inline void setPrev(Node<T>* prev) {m_prev = prev;}
   inline void setWeight(int weight) {m_weight = weight;}
   bool operator < (const PreviousWeight& item) const {
       return m_weight < item.m_weight;
   }
   bool operator > (const PreviousWeight& item) const {
       return !(*this < item);
   }
   bool operator == (const PreviousWeight& item) const {
       return m_weight == item.m_weight;
   }
   PreviousWeight& operator = (const PreviousWeight& item) = default;

private:
   Node<T>* m_prev;
   int m_weight;
};

template <class T>
PreviousWeight<T>::PreviousWeight(int weight, Node<T>* prev):m_weight(weight), m_prev(prev)
{
}
template <class T>
PreviousWeight<T>::PreviousWeight()
{
   m_prev = nullptr;
   m_weight = 0;
}

template <class T>
struct CompareNodes
{
    bool operator()(const T& node1, const T& node2) const
    {
       // assert(false);
        return  node1.second < node2.second;
    }

   // bool operator()(Node<T>* const& node1, Node<T>* const& node2) const
   // {
   //     //assert(false);
   //     return true;//node1->second < node2->second;
   // }
};

template <class T>
class ShortestPathProblem
{
public:
    typedef   std::pair<Node<T>*, PreviousWeight<T>> NodePair;
    //typedef   CompareNodes<NodeIntPair> Compare;

    ShortestPathProblem();
    static std::vector<Node<T>*> shortestPath(Graph<T> obj, Node<T>* start, Node<T>* end);
    static std::vector<Node<T>*> getPathFromMap(const std::map<Node<T>*, PreviousWeight<T>>& map, Node<T>* start, Node<T>* end);

private:
    template<class EKey, class ValueType>
    static std::pair<EKey, ValueType> getSmallerValue(const std::map<EKey,ValueType>& map);

};

template <class T>
ShortestPathProblem<T>::ShortestPathProblem()
{

}

template <class T>
std::vector<Node<T>*> ShortestPathProblem<T>::shortestPath(Graph<T> obj, Node<T>* start, Node<T>* end)
{

    std::map<Node<T>*, PreviousWeight<T>>   pQueueValues;
    auto dfsVec = obj.DFS();
    std::list<Node<T>*> dfs(dfsVec.begin(), dfsVec.end()); //= obj.DFS();
    std::vector<Node<T>*> path;
    path.push_back(start);

    // assign all unvisited nodes infinite value
    auto it = dfs.begin();
    while(it != dfs.end()) {
        if(*it != start) {
            pQueueValues.insert(NodePair(*it, PreviousWeight<T>(std::numeric_limits<int>::max())));
        }
        ++it;
    }

    pQueueValues.insert(NodePair(start, PreviousWeight<T>(0, start)));
    // the smallest weighted node in each iterartion
    Node<T>* smallWeight = start;
    while(!dfs.empty()) {
        std::vector<std::pair<Node<T>*, int>> neighbors = obj.getNeighboursWithWeight(smallWeight);
        auto it = neighbors.begin();
        dfs.remove(smallWeight);
        while(it != neighbors.end()) {
            int newWeight = it->second+pQueueValues[smallWeight].weight();
            if(pQueueValues[it->first].weight() > newWeight) {
                pQueueValues[it->first].setWeight(newWeight);
                pQueueValues[it->first].setPrev(smallWeight);
            }
            ++it;
        }

        Node<T>* smallerPrev = pQueueValues[smallWeight].prev();
        pQueueValues[smallWeight].setWeight(std::numeric_limits<int>::max());
        obj.deleteNode(smallWeight);

        smallWeight = getSmallerValue(pQueueValues).first;
        if(smallWeight == end) {
            break;
        }
    }

    path = getPathFromMap(pQueueValues, start, end);
    return path;
}

template<class T>
template <class EKey, class ValueType>
std::pair<EKey, ValueType> ShortestPathProblem<T>::getSmallerValue(const std::map<EKey, ValueType>& map)
{
    std::pair<EKey, ValueType> minValuePair(nullptr, PreviousWeight<T>(std::numeric_limits<int>::max()));
    auto findMinValue = [&minValuePair](const std::pair<EKey, ValueType>& pair) { if(pair.second < minValuePair.second) { minValuePair.second = pair.second;
                                                                                                                         minValuePair.first = pair.first;}};
    std::for_each(map.begin(), map.end(), findMinValue);
    return minValuePair;
}

template <class T>
std::vector<Node<T>*> ShortestPathProblem<T>::getPathFromMap(const std::map<Node<T>*, PreviousWeight<T>>& map, Node<T>* start, Node<T>* end)
{
    std::vector<Node<T>*> path;

    Node<T>* findNode =  end;
    while(true) {
        path.push_back(findNode);
        if(findNode == start)
            break;
        auto walk = map.find(findNode);
        findNode = walk->second.prev();

    }
    std::reverse(path.begin(), path.end());
    return path;
}
#endif // SHORTESTPATHPROBLEM_H
