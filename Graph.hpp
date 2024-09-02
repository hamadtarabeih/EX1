#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

namespace ariel {
    class Graph {
        public:
            Graph();
            ~Graph();

            // Load the graph from the adjacency matrix
            void loadGraph(const std::vector<std::vector<int>> &adjacencyMatrix);

            // Print the graph (for debugging purposes)
            void printGraph() const;

            // Get the number of vertices in the graph
            unsigned int getNumVertices() const;

            // Get the number of edges in the graph
            int getNumEdges() const;

            // Check if there is an edge from u to v
            bool containsEdge(unsigned int u, unsigned int v) const;

            // return array of neighbors
            unsigned int *getNeighbors(unsigned int u, unsigned int &size) const;

            // return the weight between u and v
            int getWeight(unsigned int u, unsigned int v) const;

            // Arithmetic operators
            Graph operator+(const Graph &graph) const;
            Graph &operator+=(const Graph &graph);
            Graph operator-(const Graph &graph) const;
            Graph &operator-=(const Graph &graph);
            Graph operator+() const; // Unary plus
            Graph operator-() const; // Unary minus

            // Comparison operators
            bool operator==(const Graph &graph) const;
            bool operator!=(const Graph &graph) const;
            bool operator<(const Graph &graph) const;
            bool operator<=(const Graph &graph) const;
            bool operator>(const Graph &graph) const;
            bool operator>=(const Graph &graph) const;

            // Increment and decrement operators
            Graph& operator++();   // Prefix increment
            Graph operator++(int); // Postfix increment
            Graph& operator--();   // Prefix decrement
            Graph operator--(int); // Postfix decrement

            // Scalar multiplication
            Graph operator*(int scalar) const;
            Graph &operator*=(int scalar);

            // Graph multiplication
            Graph operator*(const Graph &graph) const;

            // Output operator
            friend std::ostream &operator<<(std::ostream &os, const Graph &graph);
        private:
            std::vector<std::vector<int>> adjacencyMatrix;

    };

} // namespace ariel

#endif // GRAPH_HPP
