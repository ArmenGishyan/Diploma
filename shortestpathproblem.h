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
    static std::vector<Node<T>*> shortestPath(Graph<T>& obj, Node<T>* start, Node<T>* end);

private:
    template<class EKey, class ValueType>
    static std::pair<EKey, ValueType> getSmallerValue(const std::map<EKey,ValueType>& map);

};

template <class T>
ShortestPathProblem<T>::ShortestPathProblem()
{

}

template <class T>
std::vector<Node<T>*> ShortestPathProblem<T>::shortestPath(Graph<T>& obj, Node<T>* start, Node<T>* end)
{

    std::map<Node<T>*, int>   pQueueValues;
    std::vector<Node<T>*> dfs = obj.DFS();

    pQueueValues.insert(NodeIntPair(start,0));
    std::vector<Node<T>*> path;

    // assign all unvisited nodes infinite value
    for(int i = 0; i < dfs.size()-1; ++i) {
        if(dfs[i] != start) {
            pQueueValues.insert(NodeIntPair(dfs[i], std::numeric_limits<int>::max()));
        }
    }

    pQueueValues.insert(NodeIntPair(start, 0));
    // the smallest weighted node in each iterartion
    Node<T>* smallWeight = start;
    for(int i = 0; i < obj.m_adj.size(); ++i) {
        if(obj.m_adj[i].begin()->first == smallWeight) {
            // Current Searchable Line in Graph
            auto searchLine = obj.m_adj[i].begin();
            while(searchLine != obj.m_adj[i].end()) {
                if(pQueueValues[searchLine->first] > searchLine->second) {
                    pQueueValues[searchLine->first] = searchLine->second + pQueueValues[smallWeight];
                }

                ++searchLine;
            }

            path.push_back(smallWeight);
            obj.deleteNode(smallWeight);
        }

        smallWeight = getSmallerValue(pQueueValues).first;
    }

    return path;
}

template<class T>
template <class EKey, class ValueType>
std::pair<EKey, ValueType> ShortestPathProblem<T>::getSmallerValue(const std::map<EKey, ValueType>& map)
{
    std::pair<EKey, ValueType> minValuePair(nullptr, std::numeric_limits<int>::max());
    auto findMinValue = [&minValuePair](const std::pair<EKey, ValueType>& pair) { if(pair.second > minValuePair.second)  minValuePair.second = pair.second;};
    std::for_each(map.begin(), map.end(), findMinValue);
    return minValuePair;
}

#endif // SHORTESTPATHPROBLEM_H
