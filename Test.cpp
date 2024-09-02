#include "doctest.h"
#include "Graph.hpp"
#include <sstream>

using namespace ariel;

TEST_CASE("Test Arithmetic Operators with Exceptions")
{
    Graph g1, g2;
    std::vector<std::vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    std::vector<std::vector<int>> graph2 = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}};
    std::vector<std::vector<int>> graph3 = {
        {0, 1},
        {1, 0}};

    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    Graph g3;
    g3.loadGraph(graph3);

    // Test valid operations
    Graph g4 = g1 + g3;
    CHECK(g4.getWeight(0, 1) == 2);

    g1 += g3;
    CHECK(g1.getWeight(0, 1) == 2);

    Graph g5 = g1 - g3;
    CHECK(g5.getWeight(0, 1) == 1);

    g1 -= g3;
    CHECK(g1.getWeight(0, 1) == 1);

    // Test exceptions
    CHECK_THROWS(g1 + g2);
    CHECK_THROWS(g1 += g2);
    CHECK_THROWS(g1 - g2);
    CHECK_THROWS(g1 -= g2);
}

TEST_CASE("Test Comparison Operators with Logic")
{
    Graph g1, g2, g3;
    std::vector<std::vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    std::vector<std::vector<int>> graph2 = {
        {0, 1},
        {1, 0}};
    std::vector<std::vector<int>> graph3 = {
        {0, 1},
        {2, 0}};

    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g3.loadGraph(graph3);

    // Test equality
    CHECK(g1 == g2);
    CHECK_FALSE(g1 != g2);

    // Test containment and edge comparison
    CHECK(g3 > g1);
    CHECK(!(g1 < g3));

    // Test same edge count but different size
    Graph g4;
    std::vector<std::vector<int>> graph4 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g4.loadGraph(graph4);
    CHECK(g4 > g1);
    CHECK(g1 < g4);

    // Test greater than or equal / less than or equal
    CHECK(g1 <= g2);
    CHECK(g2 >= g1);
    CHECK(g4 >= g1);
    CHECK(g1 <= g4);
}

TEST_CASE("Test Unary Operators with Edge Modification")
{
    Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);

    Graph g1 = +g;
    CHECK(g1 == g);

    Graph g2 = -g;
    CHECK(g2.getWeight(0, 1) == -1);
    CHECK(g2.getWeight(1, 0) == -1);
}

TEST_CASE("Test Increment and Decrement Operators with Edge Weight Adjustment")
{
    Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);

    Graph g1 = ++g;
    CHECK(g1.getWeight(0, 1) == 2);

    Graph g2 = g++;
    CHECK(g2.getWeight(0, 1) == 2);
    CHECK(g.getWeight(0, 1) == 3);

    Graph g3 = --g;
    CHECK(g3.getWeight(0, 1) == 2);

    Graph g4 = g--;
    CHECK(g4.getWeight(0, 1) == 2);
    CHECK(g.getWeight(0, 1) == 1);
}

TEST_CASE("Test Scalar Multiplication")
{
    Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);

    Graph g1 = g * 3;
    CHECK(g1.getWeight(0, 1) == 3);

    g *= 2;
    CHECK(g.getWeight(0, 1) == 2);
}

TEST_CASE("Test Graph Multiplication with Exception")
{
    Graph g1, g2, g3;
    std::vector<std::vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    std::vector<std::vector<int>> graph2 = {
        {0, 2},
        {2, 0}};
    std::vector<std::vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};

    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    g3.loadGraph(graph3);

    // Test valid multiplication (2x2 matrices)
    Graph g4 = g1 * g2;
    CHECK(g4.getWeight(0, 0) == 2); // 1*2 + 0*2 = 2
    CHECK(g4.getWeight(0, 1) == 0); // 0
    CHECK(g4.getWeight(1, 0) == 0); // 0
    CHECK(g4.getWeight(1, 1) == 2); // 2*1 + 0*0 = 2

    // Test size mismatch exception (2x2 and 3x3 matrices)
    CHECK_THROWS(g1 * g3);
}

TEST_CASE("Test Output Operator")
{
    Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);

    std::ostringstream os;
    os << g;
    CHECK(os.str() == "[[0, 1], [1, 0]]");
}
