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
struct CompareNodes
{
    bool operator()(const T& node1, const T& node2) const
    {
        qDebug()<<"Compare Work";
       // assert(false);
        return  node1.second < node2.second;
    }

   // bool operator()(Node<T>* const& node1, Node<T>* const& node2) const
   // {
   //     qDebug()<<"Compare Work";
   //     //assert(false);
   //     return true;//node1->second < node2->second;
   // }
};

template <class T>
class ShortestPathProblem
{
public:
    typedef   std::pair<Node<T>*, int> NodeIntPair;
    typedef   CompareNodes<NodeIntPair> Compare;

    ShortestPathProblem();
    static std::vector<Node<T>*> shortestPath(Graph<T> obj, Node<T>* start, Node<T>* end);

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

    std::map<Node<T>*, int>   pQueueValues;
    auto dfsVec = obj.DFS();
    std::list<Node<T>*> dfs(dfsVec.begin(), dfsVec.end()); //= obj.DFS();

    pQueueValues.insert(NodeIntPair(start,0));
    std::vector<Node<T>*> path;

    // assign all unvisited nodes infinite value
    auto it = dfs.begin();
    while(it != dfs.end()) {
        if(*it != start) {
            pQueueValues.insert(NodeIntPair(*it, std::numeric_limits<int>::max()));
        }
        ++it;
    }

    pQueueValues.insert(NodeIntPair(start, 0));
    // the smallest weighted node in each iterartion
    Node<T>* smallWeight = start;
    while(!dfs.empty()) {
        std::vector<std::pair<Node<T>*, int>> neighbors = obj.getNeighboursWithWeight(smallWeight);
        auto it = neighbors.begin();
        dfs.remove(smallWeight);
        while(it != neighbors.end()) {
            int newWeight = it->second+pQueueValues[smallWeight];
            if(pQueueValues[it->first] > newWeight) {
                pQueueValues[it->first] = newWeight;
            }
            ++it;
        }
        std::cout<<"small weight = "<<smallWeight->name()<<std::endl;
        auto printMap = [](std::pair<Node<T>*, int> item){std::cout<<"item = "<<item.first->name()<<", "<<item.second<<"___";};
        std::for_each(pQueueValues.begin(),pQueueValues.end(),printMap);
        std::cout<<std::endl;
        pQueueValues.erase(smallWeight);
        obj.deleteNode(smallWeight);
        path.push_back(smallWeight);

        smallWeight = getSmallerValue(pQueueValues).first;
        if(smallWeight == end) {
            std::cout<<"Ending"<<std::endl;
            //path.push_back(smallWeight);
            break;
        }
    }
    return path;
}

template<class T>
template <class EKey, class ValueType>
std::pair<EKey, ValueType> ShortestPathProblem<T>::getSmallerValue(const std::map<EKey, ValueType>& map)
{
    std::pair<EKey, ValueType> minValuePair(nullptr, std::numeric_limits<int>::max());
    auto findMinValue = [&minValuePair](const std::pair<EKey, ValueType>& pair) { if(pair.second < minValuePair.second) { minValuePair.second = pair.second;
                                                                                                                         minValuePair.first = pair.first;}};
    std::for_each(map.begin(), map.end(), findMinValue);
    return minValuePair;
}

#endif // SHORTESTPATHPROBLEM_H
