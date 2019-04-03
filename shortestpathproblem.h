#ifndef SHORTESTPATHPROBLEM_H
#define SHORTESTPATHPROBLEM_H
#include "graph.h"

#include <map>
#include <limits>

template <class T>
class ShortestPathProblem
{
public:
    ShortestPathProblem();
    static std::vector<Node<T>*> shortestPath(Graph<T>& obj, Node<T>* start, Node<T>* end);
};

template <class T>
ShortestPathProblem<T>::ShortestPathProblem()
{

}

template <class T>
std::vector<Node<T>*> ShortestPathProblem<T>::shortestPath(Graph<T>& obj, Node<T>* start, Node<T>* end)
{

    std::map<Node<T>*, int> pathMap;
    std::vector<Node<T>*> dfs = obj.DFS();
    pathMap[start] = 0;
    for(int i = 0; i < dfs.size(); ++i) {
        pathMap[dfs[i]] = std::numeric_limits<int>::max();
    }

    pathMap[start] = 0;

    for(int i = 0; i < obj.m_adj.size(); ++i) {
        // the smallest weighted node in each iterartion
        Node<T>* smallWeight = obj.m_adj[i].begin()->first;
        if(obj.m_adj[i].begin()->first == smallWeight) {
            // Current Searchable Line in Graph
            auto searchLine = obj.m_adj[i].begin();
            while(searchLine != obj.m_adj[i].end()) {
                if(pathMap[searchLine->first] > searchLine->second) {
                    pathMap[searchLineqgit ->first] = searchLine->second; // + smallWeight->second;
                }

                ++searchLine;
            }
        }
    }

    std::vector<Node<T>*> path;


    return path;

}

#endif // SHORTESTPATHPROBLEM_H
