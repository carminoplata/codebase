#include "graph.hpp"

#include <string>

#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

class GraphBuilder{
public:
    GraphBuilder() = default;
    ~GraphBuilder();

    Graph<int> createGraphOfNumbers();
    Graph<std::string> createGraphOfStrings();
}; 
#endif