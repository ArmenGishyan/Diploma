#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <iostream>
#include <sstream>

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




#endif // GRAPHNODE_H
