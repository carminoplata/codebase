#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>


#ifndef NODE_H
#define NODE_H

template<class T>
class Node
{
public:
    Node() = default;
    Node(auto value) 
        : value{value}
        , visited{false}
    {
    }
    

    /**
     * @brief Give the read acces to the node
     * 
     * @return an immutable lvalue of the data in the node
     */
    const T& readValue() const {
        return value;
    }

    /**
     * @brief Get the Value object
     * 
     * @return a mutable lvalue of the data in the node
     */
    T& getValue() {
        return value;
    }

    /**
     * @brief Verify if there are neighbours around the node
     * 
     * @return true if the node has got neighbours around it
     * @return false otherwise.
     */
    bool hasAdjacents() const{
        return !adjacents.empty();
    }

    /**
     * @brief Apply the operation to the node and its neighbours
     * 
     * @param operation - function to apply at each node
     */
    void visit(auto& operation){
        operation(value);
        std::for_each(adjacents.begin(), adjacents.end(),
                      [operation](auto node){
                       node.visit(operation); 
                      });
    }

    const std::vector<Node<T>>& readAdjacents() const{
        return adjacents;
    }

    std::vector<Node<T>>& getAdjacents(){
        return adjacents;
    }

    void addAdjacents(Node<T>& node){
        adjacents.push_back(node);
    }

    Node<T>& emplaceData(auto data){
        return adjacents.emplace_back(data);
    }

    void clearVisited(){
        visited = false;
        std::for_each(adjacents.begin(), adjacents.end(),
                      [](auto node){
                        node.clearVisited();
        });
    }
    bool hasPathTo(auto& data){
        if(data==value){
            throw std::exception("The target node is the node itself");
        }
        auto isEqual =  [data](const auto& elem){
            return elem.readValue() == data;
        };
        auto it = std::ranges::find_if(adjacents, isEqual);

        return it!=adjacents.end();
    }

    auto operator<=>(const Node<T>& other) const{
        return value <=> other.value;
    }

    auto operator==(const Node<T>& other) const{
        return value == other.value;
    }

    // Members
    bool visited;

private:
    std::vector<Node<T>> adjacents;
    T value;
};

bool isThereIntersection(const std::vector<bool>& visitedA, 
                         const std::vector<bool>& visitedB,
                         int& middeNodeIndex)
{
    bool isIntersected = false;
    bool isFinished = false;

    size_t i=0;

    while (!isIntersected && i<visitedA.size())
    {
        if(visitedA[i] && visitedB[i])
        {
            std::cout << "Node at pos "<< i << " visited from both sides" << std::endl;
            isIntersected = true;
            middeNodeIndex = i;
        }else
        {
            // BOOOOOOOH 
            
        }
        ++i;
    }
    return isIntersected;
}

template<class T>
bool isThereDirectPathFromTo(const Node<T>& src, const Node<T>& dst)
{
    std::queue<Node<T>> nodesToVisitSrc;
    //std::queue<Node<T>> nodesToVisitDst;
    bool isPathFound = false;
    //nodesToVisitDst.push(dst);
    nodesToVisitSrc.push(src);
    while(!isPathFound && !nodesToVisitSrc.empty()) //|| !nodesToVisitDst.empty()))
    {
        Node<T> fromSrc = nodesToVisitSrc.front();
        //Node<T> fromDst = nodesToVisitDst.front();
        if((!fromSrc.visited && fromSrc.hasPathTo(dst.readValue()))) 
           //|| (!fromDst.visited && fromDst.hasPathTo(src.readValue())))
        {
            isPathFound = true;
        }else
        {
            if(!fromSrc.visited)
            {
                fromSrc.visited = true;
                auto adjacents = fromSrc.getAdjacents();
                std::for_each(adjacents.begin(), adjacents.end(), 
                              [&nodesToVisitSrc](auto node){
                    nodesToVisitSrc.push(node);
                });
            }
            /*if(!fromDst.visited)
            {
                fromDst.visited = true;
                auto adjacents = fromSrc.getAdjacents();
                std::for_each(adjacents.begin(), adjacents.end(), 
                              [&nodesToVisitDst](auto node){
                    nodesToVisitDst.push(node);
                });
            }*/
        }
        //nodesToVisitDst.pop();
        nodesToVisitSrc.pop();
    }

    return isPathFound;

}

template<class T>
bool isTherePathBetweenTwoNodes(const int indexA, const int indexB,
                                const std::vector<Node<T>>& graph)
{
    std::queue<int> nodesToVisitA;
    std::queue<int> nodesToVisitB;
    std::vector<int> parentsA(graph.size(), -1);
    std::vector<int> parentsB(graph.size(), -1);
    std::vector<bool> visitedA(graph.size(), false);
    std::vector<bool> visitedB(graph.size(), false);
    bool isPathFound = false;
    int indexMiddleNode = -1;
    if(indexA < 0 || static_cast<size_t>(indexA) >= graph.size() ||
       indexB < 0 || static_cast<size_t>(indexB) >= graph.size())
    {
        throw std::invalid_argument("Index of nodes are out of range");
    }

    nodesToVisitB.push(indexB);
    nodesToVisitA.push(indexA);
    while(!isPathFound && !nodesToVisitA.empty() && !nodesToVisitB.empty())
    {
        int fromA = nodesToVisitA.front();
        int fromB = nodesToVisitB.front();
        nodesToVisitA.pop();
        nodesToVisitB.pop();
        visitAdjacents(fromA, nodesToVisitA, parentsA, visitedA, graph);
        visitAdjacents(fromB, nodesToVisitB, parentsB, visitedB, graph);
        if(isThereIntersection(visitedA, visitedB, indexMiddleNode))
        {
            std::cout << "Found Intersection on Node "<< graph[indexMiddleNode].readValue();
            isPathFound = true;
        }else
        {
            
            /*if(!fromA.visited)
            {
                fromA.visited = true;
                auto adjacents = fromA.getAdjacents();
                std::for_each(adjacents.begin(), adjacents.end(), 
                              [&nodesToVisitA](auto node){
                    nodesToVisitA.push_back(node);
                });
            }
            if(!fromB.visited)
            {
                fromB.visited = true;
                auto adjacents = fromB.getAdjacents();
                std::for_each(adjacents.begin(), adjacents.end(), 
                              [&nodesToVisitB](auto node){
                    nodesToVisitB.push_back(node);
                });
            }*/
        }

    }

    return isPathFound;
}



template<class T>
void visitAdjacents(int nodeToVisit, std::queue<int>& listToVisit, std::vector<int>& parents,
                    std::vector<bool>& visited, const std::vector<Node<T>>& graph)
{
    if(graph[nodeToVisit].hasAdjacents())
    {
        std::ranges::for_each(graph[nodeToVisit].readAdjacents(), 
                              [nodeToVisit, &listToVisit,
                               &parents, &visited, &graph](auto n){
            auto nit = std::ranges::find(graph, n);
            int curr_index = nit - graph.begin();
            if(!visited[curr_index])
            {
                listToVisit.push(curr_index);
                parents[curr_index] = nodeToVisit;
                visited[curr_index] = true;
            }
        });
    }
    /*std::ranges::for_each(listOfNodesToVisit, 
                          [&listOfNodesToVisit, &parents, &visited, &graph](auto node){
            
    });*/
    visited[nodeToVisit] = true;
}
#endif