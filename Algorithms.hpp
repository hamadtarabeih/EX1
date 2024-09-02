#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>
#include <unordered_set>
#include <unordered_map>

namespace ariel {
    class Algorithms {
    public:
        // Check if the graph is connected
        static int isConnected(const Graph& g);

        // Find the shortest path between two vertices
        static std::string shortestPath(const Graph& g, unsigned int start, unsigned int end);

        // Check if the graph contains a cycle
        static int isContainsCycle(const Graph& g);

        // Check if the graph is bipartite
        static std::string isBipartite(const Graph& g);

        // Check if the graph has a negative cycle
        static bool negativeCycle(const Graph& g);

    private:
        // Helper function for checking cycle
        static bool isContainsCycleRecursive(const Graph &g, unsigned int v, std::vector<bool> &visited, std::vector<int> &parent);
        static void traverseGraph(const Graph &g, unsigned int u, bool visited[]);
    };

} // namespace ariel

#endif // ALGORITHMS_HPP
