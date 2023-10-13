#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "graph.hpp"

#include <string>



class GraphBuilder{
public:
    GraphBuilder() = default;
    ~GraphBuilder();

    Graph<int> createGraphOfNumbers();
    Graph<std::string> createGraphOfStrings();
}; 
#endif