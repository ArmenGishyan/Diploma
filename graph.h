#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <string>
#include <vector>
#include <bitset>
#include <queue>
#include <sstream>
#include <stack>
#include <utility>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <deque>
#include <type_traits>
#include <QDebug>
#include "graphnode.h"



namespace std
{
	template<>
    struct hash<std::pair<Node<int>*, int>>
	{
        size_t operator()(const std::pair<Node<int>*, int>& obj) const
		{
            std::size_t x = std::hash<std::string>{}(obj.first->name());
			return x;
		}
    };

   // template <>
   // template<class T>
   // struct remove_reference<std::pair<Node<T>*, int>>
   // {

   //     remove_reference& operator = (const remove_reference& obj)
   //     {
   //        return *this;
   //     }

   // };

   // template <>
   // std::pair<Node<int>*, int>&& forward<std::pair<Node<int>*, int>&&>(std::pair<Node<int>*, int>&& param) noexcept
   // {
   //         return move(param);
   // }
}


template<class E>
class Graph
{
public:
    typedef std::pair<Node<E>*, int> NodeType;
    typedef std::unordered_set<NodeType> AdjListType;
    typedef std::pair<Node<E>*, AdjListType> RowType;

public:

    template<class T> friend class ShortestPathProblem;
	Graph() = default;
	Graph(int nodeCount);
	void addNode(Node<E>*);
    bool connNodes(Node<E>*, Node<E>*, int weight = 1);
    bool connNodes(const std::string node1, const std::string node2, int weight = 1);
	std::vector<Node<E>*> BFS() const;
	std::vector<Node<E>*> DFS() const;
    void deleteNode(const Node<E>* node, bool force = false);
    std::vector<Node<E>*> getNodes() const;
    Node<E>* getNode(const std::string& name) const;
	void print() const;

private:
    std::vector<Node<E>*> getNeighbours(Node<E>* node) const;
    std::vector<NodeType> getNeighboursWithWeight(Node<E>* node) const;

private:
    std::deque<RowType> m_adj;
};

template<class T>
void Graph<T>::addNode(Node<T>* node)
{
    m_adj.push_back(RowType(node, AdjListType()));
 //   AdjListType nodeTemp;
 //   nodeTemp.insert(std::pair<Node<T>*, int> (node, 0));
    //m_adj.push_back(nodeTemp);
}

template<class T>
bool Graph<T>::connNodes(Node<T>* node1, Node<T>* node2, int weight)
{
    auto it = m_adj.begin();
    bool flag1 = true;
    bool flag2 = true;
    while (it != m_adj.end()) {
        if (flag1 && it->first->name() == node1->name()) {
            it->second.insert(std::pair<Node<T>*, int >(node2, weight));
            flag1 = false;
        }
        if (flag2 && it->first->name() == node2->name()) {
            it->second.insert(std::pair<Node<T>*, int >(node1, weight));
            flag2 = false;
        }
        if (!flag1 && !flag2)
            return true;
        ++it;
    }
    return false;
}

template<class T>
bool Graph<T>::connNodes(const std::string node1, const std::string node2, int weight)
{
    Node<T>* nodeFirst = getNode(node1);
    Node<T>* nodeSecond = getNode(node2);
    if(!nodeFirst || !nodeSecond)
        return false;

    return connNodes(nodeFirst, nodeSecond, weight);

}
template<class T>
void Graph<T>::print() const
{
	auto it = m_adj.begin();
    while (it != m_adj.end()) {
        std::cout << it->first->name() << ", ";
        auto itFirst = it->second.begin();
        while (itFirst != it->second.end()) {
            std::cout << itFirst->first->name() << ", ";
			itFirst++;
		}
		std::cout << std::endl;
		++it;
	}
}


template<class T>
Graph<T>::Graph(int nodeCount)
{
	for (int i = 0; i < nodeCount; ++i)
	{
		addNode(new Node<T>("A" + std::to_string(i)));
	}
}

template<class T>
std::vector<Node<T>*> Graph<T>::BFS() const
{
    std::map<Node<T>*, bool> visited;
    std::vector<Node<T>*> nodes = getNodes();

    std::for_each(nodes.begin(), nodes.end(), [&visited](Node<T>* item){visited[item] = false;});
	std::queue<Node<T>*> queue;
	std::vector<Node<T>*> BFSnods;

    queue.push(m_adj.begin()->first);
	
	while (!queue.empty()) 
	{
		Node<T>* node = queue.front();
		BFSnods.push_back(node);
		queue.pop();
        visited[node] = true;
        std::vector<Node<T>*> neighbors = getNeighbours(node);
        for (const auto& item : neighbors) {
            if (!visited[item]) {
                visited[item] = true;
                queue.push(item);
			}
        }
	}
	return BFSnods;
}

template<class T>
std::vector<Node<T>* > Graph<T>::DFS() const
{
	std::vector<Node<T>* > dfsList;
	if (m_adj.empty()) {
		return dfsList;
	}
    std::map<Node<T>*, bool> visited;
	std::stack<Node<T>* > st;

    auto firstNode = m_adj.begin()->first;
    st.push(firstNode);
    dfsList.push_back(firstNode);
    visited[firstNode] = true;
	int count = 0;
    std::vector<Node<T>*> currentRow = getNeighbours(firstNode);

	while (!st.empty()) 
	{
		count = 0;
        for (const auto& it : currentRow) {
            if (!visited[it]) {
                visited[it] = true;
                st.push(it);
                dfsList.push_back(it);
                currentRow = getNeighbours(it);
				break;
			}
			else {
				count++;
			}
		}

        if (count == currentRow.size()) {
            currentRow = getNeighbours(st.top());
			if (!st.empty()) {
				st.pop();
			}
		}
	}
	return dfsList;

}

template <class T>
void Graph<T>::deleteNode(const Node<T>* node, bool force)
{

    for(auto i = m_adj.begin(); i != m_adj.end(); ++i)
    {
        if(i->first == node) {
            i = m_adj.erase(i);
            break;
        }
    }

    for(int i = 0; i < m_adj.size(); ++i) {

        auto setItStart = m_adj[i].second.begin();
        auto setItEnd = m_adj[i].second.end();
        while (setItStart != m_adj[i].second.end()) {
            if(setItStart->first->name() == node->name()) {
                setItStart = m_adj[i].second.erase(setItStart);
                break;
            }
            ++setItStart;
        }
    }

}

template <class T>
std::vector<Node<T>*> Graph<T>::getNeighbours(Node<T>* node) const
{
    std::vector<Node<T>*> neighbours;

    auto it = m_adj.begin();
    AdjListType adjList;
    while(it != m_adj.end()) {
        if(it->first->name() == node->name()) {
            adjList = it->second;
            break;
        }
        ++it;
    }

    neighbours.reserve(adjList.size());
    for(const auto& item : adjList) {
        neighbours.push_back(item.first);
    }
    return neighbours;
}

template<class T>
std::vector<Node<T>*> Graph<T>::getNodes() const
{
    std::vector<Node<T>*> nodes;
    nodes.reserve(m_adj.size());

    for(const RowType& item : m_adj) {
        nodes.push_back(item.first);
    }
    return std::move(nodes);
}

template <class T>
std::vector<std::pair<Node<T>*,int>> Graph<T>::getNeighboursWithWeight(Node<T>* node) const
{
    assert(node);
    auto it = m_adj.begin();
    AdjListType adjList;
    while(it != m_adj.end()) {
        if(it->first->name() == node->name()) {
            adjList = it->second;
            break;
        }
        ++it;
    }

    std::vector<std::pair<Node<T>*, int>> neighbours(adjList.begin(),adjList.end());
    return std::move(neighbours);
}

template <class T>
Node<T>* Graph<T>::getNode(const std::string& name) const
{
    for(int i = 0; i< m_adj.size(); ++i) {
        if(m_adj[i].first->name() == name) {
            return m_adj[i].first;
        }
    }

    return nullptr;
}
#endif
