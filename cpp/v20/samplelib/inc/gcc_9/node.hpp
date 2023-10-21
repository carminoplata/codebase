#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

template<class T>
class Node
{
public:
    Node() = default;
    Node(T value) 
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
    void visit(std::function<void(const T&)> operation){
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

    Node<T>& emplaceData(T& data){
        return adjacents.emplace_back(data);
    }

    void clearVisited(){
        visited = false;
        std::for_each(adjacents.begin(), adjacents.end(),
                      [](auto node){
                        node.clearVisited();
        });
    }
    
    bool hasPathTo(const T& data){
        if(data==value){
            throw std::logic_error("The target node is the node itself");
        }
        auto isEqual =  [data](const Node<T>& elem){
            return elem.readValue() == data;
        };
        auto it = std::find_if(adjacents.begin(), 
            adjacents.end(),
            isEqual);

        return it!=adjacents.end();
    }

    auto operator<(const Node<T>& other) const{
        return value < other.value;
    }

    auto operator>(const Node<T>& other) const{
        return value > other.value;
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


#endif