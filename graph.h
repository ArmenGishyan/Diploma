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



template<class T>
struct Node
{
	Node(std::string name, T value = T(), int weight = 1) :
        m_name(name), value(value)
	{}
	Node() = default;
	Node(const Node& obj) = default;

	int getIndex() const
	{
        std::stringstream str(m_name);
		int x = 0;
		str >> x;
		
		return x;
	}
    std::string name() const
	{
        return m_name;
	}

	bool operator == (const Node& obj)
	{
		std::cout << "operator == " << std::endl;
		return true;
	}

private:
    std::string m_name;
	T value;
};

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
    typedef std::unordered_set<std::pair<Node<E>*, int>> AdjListType;
    typedef std::pair<Node<E>*, AdjListType> RowType;
public:

    template<class T> friend class ShortestPathProblem;
	Graph() = default;
	Graph(int nodeCount);
	void addNode(Node<E>*);
	void connNodes(Node<E>*, Node<E>*, int weight = 1);
	std::vector<Node<E>*> BFS() const;
	std::vector<Node<E>*> DFS() const;
    void deleteNode(const Node<E>* node, bool force = false);
    std::vector<Node<E>*> getNodes() const;
	void print() const;

private:
    std::vector<Node<E>*> getNeighbours(Node<E>* node) const;

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
void Graph<T>::connNodes(Node<T>* node1, Node<T>* node2, int weight)
{
    auto it = m_adj.begin();
    while (it != m_adj.end()) {
        bool flag1 = true;
        bool flag2 = true;
        if (flag1 && it->first->name() == node1->name()) {
            it->second.insert(std::pair<Node<T>*, int >(node2, weight));
            flag1 = false;
        }
        if (flag2 && it->first->name() == node2->name()) {
            it->second.insert(std::pair<Node<T>*, int >(node1, weight));
            flag2 = false;
        }
        if (!flag1 && !flag2)
            break;
        ++it;
    }
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
                qDebug()<<"dfvd";
                visited[item] = true;
                queue.push(item);
			}
        }
	}
    qDebug()<<"finish";
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
        qDebug()<<"index = "<<i;
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

