#ifndef NODEFIXTURE_H
#define NODEFIXTURE_H

#include "node.hpp"
#include "utils.hpp" 

#include <gtest/gtest.h>

#include <vector>

class NodeFixture : public testing::Test
{
public:
    NodeFixture();

protected:
    Node<std::string> node;
};

class GraphFixture : public NodeFixture
{
public:
    GraphFixture(); 

protected:
    int numNodes;
    std::vector<Node<std::string>> nodes;
};


class DirectGraphFixture : public GraphFixture
{
public:
    DirectGraphFixture(); 

protected:
};

#endif