#pragma once
#include "Graph.h"
#include <vector>

class Dijkstra {
public:
    // Returns the shortest path as a list of node indices
   
    static std::vector<int> findPath(const Graph& graph, int src, int dest);
};