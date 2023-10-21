#ifndef GRAPH_H
#define GRAPH_H

#include "node.hpp"

#include <memory>

template<class T>
class Graph
{

public:
    Graph()
        : initNode{nullptr}
        , num_nodes{0}
    {    
    };

    Graph(const T& data)
        : initNode{new Node<T>(data)}
        , num_nodes{1}
    {

    }

    ~Graph();

    Graph(const Graph<T>&& other);
    Graph<T>& operator=(const Graph<T>&& other);

    Graph(const Graph& other) = delete;
    Graph& operator=(const Graph& other) = delete;

    int getNumNodes() const
    {
        return num_nodes;
    }

    void addNode(const T& data)
    {
        if(initNode==nullptr)
        {
            initNode = new Node(data);
        }else
        {
            initNode->emplaceData(data);
        }
    }

private:
    /* data */
    std::unique_ptr<T> initNode;
    int num_nodes;
};




#endif