#pragma once
#include <vector>
#include <string>

struct Edge {
    int to;        // destination node index
    int weight;    // link cost (latency in ms)
};

struct Node {
    std::string name;   // e.g. "Router A"
    float x, y;         // position on screen for drawing
};

class Graph {
public:
    std::vector<Node> nodes;
    std::vector<std::vector<Edge>> adjList;

    void addNode(const std::string& name, float x, float y);
    void addEdge(int from, int to, int weight);
    int nodeCount() const;
};

