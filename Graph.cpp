#include <iostream>
#include "Graph.hpp"

namespace ariel
{
    // Constructor
    Graph::Graph() {}

    // Destructor
    Graph::~Graph() {}

    // Load the graph from the adjacency matrix
    void Graph::loadGraph(const std::vector<std::vector<int>> &adjacencyMatrix)
    {
        unsigned int num = adjacencyMatrix.size();
        for (unsigned int i = 0; i < num; i++)
        {
            if (num != adjacencyMatrix[i].size())
            {
                throw std::invalid_argument("Not square");
            }
            for (unsigned int j = 0; j < num; j++)
            {
                if (j == i && adjacencyMatrix[i][j] != 0)
                {
                    throw std::invalid_argument("Invalid values");
                }
            }
        }
        this->adjacencyMatrix = adjacencyMatrix;
    }

    void Graph::printGraph() const
    {
        unsigned int num = getNumVertices();
        int edges = getNumEdges();
        std::cout << "Graph with " << num << " vertices and " << edges << " edges." << std::endl;
    }

    unsigned int Graph::getNumVertices() const
    {
        return adjacencyMatrix.size();
    }

    int Graph::getNumEdges() const
    {
        int count = 0;
        for (unsigned int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (unsigned int j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                if (adjacencyMatrix[i][j] != 0)
                {
                    count++;
                }
            }
        }
        return count / 2;
    }

    bool Graph::containsEdge(unsigned int u, unsigned int v) const
    {
        if (adjacencyMatrix[u][v] != 0)
        {
            return true;
        }
        return false;
    }

    unsigned int *Graph::getNeighbors(unsigned int u, unsigned int &size) const
    {
        unsigned int neighborsCount = 0;
        for (unsigned int i = 0; i < adjacencyMatrix.size(); i++)
        {
            if (containsEdge(u, i))
            {
                neighborsCount++;
            }
        }

        unsigned int *neighbors = new unsigned int[neighborsCount];
        size = 0;
        for (unsigned int i = 0; i < adjacencyMatrix.size() && size != neighborsCount; i++)
        {
            if (containsEdge(u, i))
            {
                neighbors[size] = i;
                size++;
            }
        }
        return neighbors;
    }

    int Graph::getWeight(unsigned int u, unsigned int v) const
    {
        return adjacencyMatrix[u][v];
    }

    // Arithmetic operators
    Graph Graph::operator+(const Graph &other) const
    {
        if (getNumVertices() != other.getNumVertices())
        {
            throw std::invalid_argument("Graphs must be of the same size.");
        }
        Graph result = *this;
        for (unsigned int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (unsigned int j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                result.adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }
        return result;
    }

    Graph &Graph::operator+=(const Graph &other)
    {
        if (getNumVertices() != other.getNumVertices())
        {
            throw std::invalid_argument("Graphs must be of the same size.");
        }
        for (unsigned int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (unsigned int j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
            }
        }
        return *this;
    }

    Graph Graph::operator-(const Graph &other) const
    {
        if (getNumVertices() != other.getNumVertices())
        {
            throw std::invalid_argument("Graphs must be of the same size.");
        }
        Graph result = *this;
        for (unsigned int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (unsigned int j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                result.adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }
        return result;
    }

    Graph &Graph::operator-=(const Graph &other)
    {
        if (getNumVertices() != other.getNumVertices())
        {
            throw std::invalid_argument("Graphs must be of the same size.");
        }
        for (unsigned int i = 0; i < adjacencyMatrix.size(); ++i)
        {
            for (unsigned int j = 0; j < adjacencyMatrix[i].size(); ++j)
            {
                adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
            }
        }
        return *this;
    }

    Graph Graph::operator+() const
    {
        return *this;
    }

    Graph Graph::operator-() const
    {
        Graph result = *this;
        for (auto &row : result.adjacencyMatrix)
        {
            for (auto &val : row)
            {
                val = -val;
            }
        }
        return result;
    }

    // Comparison operators
    bool Graph::operator==(const Graph &other) const
    {
        return adjacencyMatrix == other.adjacencyMatrix;
    }

    bool Graph::operator!=(const Graph &other) const
    {
        return !(*this == other);
    }

    bool Graph::operator<(const Graph &other) const
    {
        if (adjacencyMatrix == other.adjacencyMatrix)
        {
            return false;
        }
        int otherEdges = other.getNumEdges();
        return (getNumEdges() < otherEdges) || (getNumEdges() == otherEdges && getNumVertices() < other.getNumVertices());
    }

    bool Graph::operator<=(const Graph &other) const
    {
        return *this < other || *this == other;
    }

    bool Graph::operator>(const Graph &other) const
    {
        return !(*this <= other);
    }

    bool Graph::operator>=(const Graph &other) const
    {
        return !(*this < other);
    }

    // Increment and decrement operators
    Graph &Graph::operator++()
    {
        for (auto &row : adjacencyMatrix)
        {
            for (auto &val : row)
            {
                ++val;
            }
        }
        return *this;
    }

    Graph Graph::operator++(int)
    {
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    Graph &Graph::operator--()
    {
        for (auto &row : adjacencyMatrix)
        {
            for (auto &val : row)
            {
                --val;
            }
        }
        return *this;
    }

    Graph Graph::operator--(int)
    {
        Graph temp = *this;
        --(*this);
        return temp;
    }

    // Scalar multiplication
    Graph Graph::operator*(int scalar) const
    {
        Graph result = *this;
        for (auto &row : result.adjacencyMatrix)
        {
            for (auto &val : row)
            {
                val *= scalar;
            }
        }
        return result;
    }

    Graph &Graph::operator*=(int scalar)
    {
        for (auto &row : adjacencyMatrix)
        {
            for (auto &val : row)
            {
                val *= scalar;
            }
        }
        return *this;
    }

    // Graph multiplication
    Graph Graph::operator*(const Graph &other) const
    {
        if (getNumVertices() != other.getNumVertices())
        {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }
        using size_type = typename std::vector<int>::size_type;
        Graph result;
        result.loadGraph(std::vector<std::vector<int>>(static_cast<size_type>(getNumVertices()), std::vector<int>(static_cast<size_type>(getNumVertices()), 0)));

        for (size_type i = 0; i < static_cast<size_type>(getNumVertices()); ++i)
        {
            for (size_type j = 0; j < static_cast<size_type>(getNumVertices()); ++j)
            {
                for (size_type k = 0; k < static_cast<size_type>(getNumVertices()); ++k)
                {
                    result.adjacencyMatrix[i][j] += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
            }
        }
        return result;
    }

    // Output operator
    std::ostream &operator<<(std::ostream &os, const Graph &graph)
    {
        os << "[";
        for (unsigned int i = 0; i < graph.adjacencyMatrix.size(); ++i)
        {
            os << "[";
            for (unsigned int j = 0; j < graph.adjacencyMatrix[i].size(); ++j)
            {
                os << graph.adjacencyMatrix[i][j];
                if (j < graph.adjacencyMatrix[i].size() - 1)
                {
                    os << ", ";
                }
            }
            os << "]";
            if (i < graph.adjacencyMatrix.size() - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
} // namespace ariel