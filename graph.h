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



template<class T>
struct Node
{
	Node(std::string name, T value = T(), int weight = 1) :
		name(name), value(value)
	{}
	Node() = default;
	Node(const Node& obj) = default;

	int getIndex() const
	{
		std::stringstream str(name);
		int x = 0;
		str >> x;
		
		return x;
	}
	std::string getName() const
	{
		return name;
	}

	bool operator == (const Node& obj)
	{
		std::cout << "operator == " << std::endl;
		return true;
	}


	std::string name;
	T value;
};

namespace std
{
	template<>
    struct hash<std::pair<Node<int>*, int>>
	{
        size_t operator()(const std::pair<Node<int>*, int>& obj) const
		{
			std::size_t x = std::hash<std::string>{}(obj.first->getName());
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
    typedef std::unordered_set<std::pair<Node<E>*, int> > AdjListType;
public:

    template<class T> friend class ShortestPathProblem;
	Graph() = default;
	Graph(int nodeCount);
	void addNode(Node<E>*);
	void connNodes(Node<E>*, Node<E>*, int weight = 1);
	std::vector<Node<E>*> BFS() const;
	std::vector<Node<E>*> DFS() const;
    void deleteNode(const Node<E>* node, bool force = false);
	void print() const;


private:
    std::deque<AdjListType> m_adj;
};

template<class T>
void Graph<T>::addNode(Node<T>* node)
{
    AdjListType nodeTemp;
    nodeTemp.insert(std::pair<Node<T>*, int> (node, 0));
	m_adj.push_back(nodeTemp);
}

template<class T>
void Graph<T>::connNodes(Node<T>* node1, Node<T>* node2, int weight)
{
	auto it = m_adj.begin();
	while (it != m_adj.end()) {
		bool flag1 = true;
		bool flag2 = true;
		auto itFirst = it->begin();
		if (flag1 && (*itFirst).first->name == node1->name) {
			it->insert(std::pair<Node<T>*, int >(node2, weight));
			flag1 = false;
		}
		if (flag2 && (*itFirst).first->name == node2->name) {
			it->insert(std::pair<Node<T>*, int >(node1, weight));
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
		auto itFirst = it->begin();
		while (itFirst != it->end()) {
			std::cout << itFirst->first->name << ", ";
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
	std::bitset<100> visited;
	std::queue<Node<T>*> queue;
	std::vector<Node<T>*> BFSnods;

	auto it = m_adj.begin();
	queue.push(it->begin()->first);
	
	visited[0] = true;
	while (!queue.empty()) 
	{
		Node<T>* node = queue.front();
		BFSnods.push_back(node);
		queue.pop();
		int index = node->getIndex();
		visited[index] = true;

		for (auto const& item : m_adj[index]) {
			if (!visited[item.first->getIndex()]) {
				visited[item.first->getIndex()] = true;
				queue.push(item.first);
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
	std::bitset<10> visited;
	std::stack<Node<T>* > st;

	st.push(m_adj[0].begin()->first);
	dfsList.push_back(m_adj[0].begin()->first);
	visited[m_adj[0].begin()->first->getIndex()] = true;
	int count = 0;
    AdjListType current = m_adj[0];

	while (!st.empty()) 
	{
		count = 0;
		for (auto it = current.begin(); it != current.end(); ++it) {
			if (!visited[it->first->getIndex()]) {
				visited[it->first->getIndex()] = true;
				st.push(it->first);
				dfsList.push_back(it->first);
				current = m_adj[it->first->getIndex()];
				break;
			}
			else {
				count++;
			}
		}

		if (count == current.size()) {
			current = m_adj[st.top()->getIndex()];
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
        if(i->begin()->first == node) {
            m_adj.erase(i);
            break;
        }
    }

    for(int i = 0; i < m_adj.size(); ++i) {

        auto setIt = m_adj[i].begin();
        while (setIt != m_adj[i].end()) {
            if(setIt->first == node) {
                setIt = m_adj[i].erase(setIt);
            }
            ++setIt;
        }
    }

}
