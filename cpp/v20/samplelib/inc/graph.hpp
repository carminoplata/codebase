#include "node.hpp"
#ifndef GRAPH_H
#define GRAPH_H

template<class T>
class Graph
{

public:
    Graph()
        : size{0}
        , initNode{nullptr}
    {    
    };

    Graph(const T& data)
        : size{1}
        , initNode{new Node<T>(data)}
    {

    }

    ~Graph();

    Graph(const Graph<T>&& other);
    Graph<T>& operator=(const Graph<T>&& other);

    Graph(const Graph& other) = delete;
    Graph& operator=(const Graph& other) = delete

    int getNumNodes()
    {
        return size;
    }

    std::string getVersion()
    {
        return LIB_VERSION;
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
    int size;
    std::unique_ptr<T> initNode;

};




#endif