
# Graph Algorithms and Operations - Assignment 1 Summer Ariel

## Graph Class

The `Graph` class represents a graph using an adjacency matrix. This class includes a variety of methods for basic graph operations, arithmetic, comparison, and more.

### Basic Operations

- **`loadGraph(const std::vector<std::vector<int>>& adjacencyMatrix)`**: Loads the graph from a given adjacency matrix. It ensures that the input matrix is square and valid.

- **`printGraph() const`**: Prints the graph's details, including the number of vertices and edges.

- **`getNumVertices() const`**: Returns the number of vertices in the graph.

- **`getNumEdges() const`**: Returns the number of edges in the graph.

- **`containsEdge(unsigned int u, unsigned int v) const`**: Checks if there is an edge between vertices `u` and `v`.

- **`getNeighbors(unsigned int u, unsigned int &size) const`**: Returns an array of neighbors for vertex `u`.

- **`getWeight(unsigned int u, unsigned int v) const`**: Returns the weight of the edge between vertices `u` and `v`.

### Arithmetic Operators

- **`operator+(const Graph &graph) const`**: Adds two graphs. Both graphs must have the same number of vertices.

- **`operator+=(const Graph &graph)`**: Adds another graph to the current graph in place.

- **`operator-(const Graph &graph) const`**: Subtracts one graph from another. Both graphs must have the same number of vertices.

- **`operator-=(const Graph &graph)`**: Subtracts another graph from the current graph in place.

- **`operator+() const`**: Unary plus operator. Returns the graph as is.

- **`operator-() const`**: Unary minus operator. Negates the weights of all edges in the graph.

### Comparison Operators

- **`operator==(const Graph &graph) const`**: Checks if two graphs are equal by comparing their adjacency matrices.

- **`operator!=(const Graph &graph) const`**: Checks if two graphs are not equal.

- **`operator<(const Graph &graph) const`**: Compares two graphs based on the number of edges and vertices.

- **`operator<=(const Graph &graph) const`**: Checks if one graph is less than or equal to another.

- **`operator>(const Graph &graph) const`**: Checks if one graph is greater than another.

- **`operator>=(const Graph &graph) const`**: Checks if one graph is greater than or equal to another.

### Increment and Decrement Operators

- **`operator++()`**: Prefix increment. Increments the weights of all edges by 1.

- **`operator++(int)`**: Postfix increment. Increments the weights of all edges by 1 but returns the graph before incrementing.

- **`operator--()`**: Prefix decrement. Decrements the weights of all edges by 1.

- **`operator--(int)`**: Postfix decrement. Decrements the weights of all edges by 1 but returns the graph before decrementing.

### Scalar and Graph Multiplication

- **`operator*(int scalar) const`**: Multiplies all edge weights by a scalar.

- **`operator*=(int scalar)`**: Multiplies all edge weights by a scalar in place.

- **`operator*(const Graph &graph) const`**: Multiplies two graphs' adjacency matrices, similar to matrix multiplication. The graphs must have compatible dimensions.

### Output Operator

- **`operator<<(std::ostream &os, const Graph &graph)`**: Outputs the graph's adjacency matrix to a stream in a readable format.

## Algorithms Class

The `Algorithms` class provides various static methods to perform common graph algorithms on instances of the `Graph` class.

### Graph Connectivity

- **`isConnected(const Graph& g)`**: Checks if the graph is connected, meaning there's a path between any two vertices.

### Shortest Path

- **`shortestPath(const Graph& g, unsigned int start, unsigned int end)`**: Finds the shortest path between two vertices in the graph using breadth-first search (BFS).

### Cycle Detection

- **`isContainsCycle(const Graph& g)`**: Checks if the graph contains any cycles.

### Bipartite Check

- **`isBipartite(const Graph& g)`**: Checks if the graph is bipartite and returns the two partitions if it is.

### Negative Cycle Detection

- **`negativeCycle(const Graph& g)`**: Detects the presence of a negative cycle in the graph using the Bellman-Ford algorithm.

## Compilation and Execution

To compile the project, use the provided `Makefile`. The following commands can be used:

```bash
make
./demo
```

This will compile and run the demo, displaying the output of various graph operations and algorithms.
