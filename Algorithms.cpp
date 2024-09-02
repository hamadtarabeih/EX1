#include <iostream>
#include "Algorithms.hpp"
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <limits>

namespace ariel {
    int Algorithms::isConnected(const Graph &g) {
        unsigned int num = g.getNumVertices();
        bool *vis = new bool[num];
        for (unsigned int u = 0; u < num; u++){
            for (unsigned int i = 0; i < num; i++){
                vis[i] = false;
            }
            
            traverseGraph(g, u, vis);
            
            for (unsigned int i = 0; i < num; i++){
                if (!vis[i]) {
                    return 0;
                }
            }
        }
        return 1;
    }

    std::string Algorithms::shortestPath(const Graph &g, unsigned int start, unsigned int end){
        unsigned int n = g.getNumVertices();
        std::queue<unsigned int> q;
        std::vector<bool> visited(n, false);
        std::vector<int> parent(n, -1);
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            unsigned int current = q.front();
            q.pop();

            for (unsigned int neighbor = 0; neighbor < n; neighbor++) {
                if (!visited[neighbor] && g.containsEdge(current, neighbor)) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = (int) current;

                    if (neighbor == end) {
                        std::string path;
                        unsigned int node = end;
                        while (node != start) {
                            if (node != end) {
                                path = std::to_string(node) + "->" + path;
                            } else {
                                path = std::to_string(node) + path;
                            }
                            node = (unsigned int) parent[node];
                        }
                        return std::to_string(start) + "->" + path;
                    }
                }
            }
        }
        return "-1";
    }

    int Algorithms::isContainsCycle(const Graph &g) {
        unsigned int num = g.getNumVertices();
        std::vector<bool> visited(num, false);
        std::vector<int> parent(num, -1);

        for (unsigned int i = 0; i < num; ++i) {
            if (!visited[i]) {
                parent[i] = -1;
                if (isContainsCycleRecursive(g, i, visited, parent)){
                    return 1;
                }
            }
        }
        return 0;
    }
    
    std::string Algorithms::isBipartite(const Graph &g) {
        unsigned int src = 0;
        unsigned int num = g.getNumVertices();
        int colorArr[num];
        for (int i = 0; i < num; ++i)
            colorArr[i] = -1;
        colorArr[src] = 1;
        std::queue<unsigned int> q;
        q.push(src);

        while (!q.empty()) {
            unsigned int u = q.front();
            q.pop();

            for (unsigned int v = 0; v < num; ++v) {
                if (g.containsEdge(u, v) && colorArr[v] == -1) {
                    colorArr[v] = 1 - colorArr[u];
                    q.push(v);
                } else if (g.containsEdge(u, v) && colorArr[v] == colorArr[u]) {
                    return "0";
                }
            }
        }

        std::string partitionA = "";
        std::string partitionB = "";
        for (unsigned int i = 0; i < num; ++i) {
            if (colorArr[i] == 1) {
                partitionA += std::to_string(i) + ", ";
            } else {
                partitionB += std::to_string(i) + ", ";
            }
        }
        for (int i = 0; i < 2; ++i) { //remove the last two chars, the ", "
            partitionA.pop_back();
            partitionB.pop_back();
        }

        return "The graph is bipartite: A={" + partitionA + "}, B={" + partitionB + "}";
    }
    
    // Using bellman ford algorithm for detecting negative cycle
    bool Algorithms::negativeCycle(const Graph &g) {
        unsigned int num = g.getNumVertices();
        std::vector<int> dist(num, std::numeric_limits<int>::max());
        dist[0] = 0;

        for (unsigned int i = 0; i < num - 1; i++) {
            for (unsigned int u = 0; u < num; u++) {
                for (unsigned int v = 0; v < num; v++) {
                    if (g.containsEdge(u, v) && dist[u] != std::numeric_limits<int>::max()) {
                        if(dist[u] + g.getWeight(u, v) < dist[v]) {
                            dist[v] = dist[u] + g.getWeight(u, v);
                        }
                    }
                }
            }
        }

        for (unsigned int u = 0; u < num; ++u) {
            for (unsigned int v = 0; v < num; ++v) {
                if (g.containsEdge(u, v) && dist[u] != std::numeric_limits<int>::max() && dist[u] + g.getWeight(u, v) < dist[v]) {
                    std::cout << "Negative cycle found!" << std::endl;
                    return true;
                }
            }
        }

        std::cout << "No negative cycle found." << std::endl;
        return false;
    }

    void Algorithms::traverseGraph(const Graph &g, unsigned int u, bool visited[]) {
        visited[u] = true;
        unsigned int num = g.getNumVertices();
        for (unsigned int v = 0; v < num; v++) {
            if (g.containsEdge(u, v)) {
                if (!visited[v]) {
                    traverseGraph(g, v, visited);
                }
            }
        }
    }

    bool Algorithms::isContainsCycleRecursive(const Graph &g, unsigned int v, std::vector<bool> &visited, std::vector<int> &parent) {
        visited[v] = true;
        unsigned int size;
        unsigned int *neighbors = g.getNeighbors(v, size);

        for (unsigned int i = 0; i < size; i++) {
            unsigned int u = neighbors[i];
            if (!visited[u]) {
                parent[u] = (int)v;
                if (isContainsCycleRecursive(g, u, visited, parent))
                    return true;
            } else if (u != parent[v]) {
                std::cout << "Cycle found: ";
                std::stack<unsigned int> cycleStack;
                cycleStack.push(u);
                for (unsigned int x = v; x != u; x = (unsigned int) parent[x]){
                    cycleStack.push(x);
                }
                cycleStack.push(u);

                while (!cycleStack.empty()) {
                    std::cout << cycleStack.top() << " ";
                    cycleStack.pop();
                }
                std::cout << std::endl;
                return true;
            }
        }
        return false;
    }
} // namespace ariel