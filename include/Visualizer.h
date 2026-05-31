#pragma once
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <vector>

class Visualizer {
public:
    Visualizer(sf::RenderWindow& window);

    void drawGraph(const Graph& graph);
    void drawPath(const Graph& graph, const std::vector<int>& path);

private:
    sf::RenderWindow& window;
    sf::Font font;
    bool fontLoaded = false;

    void drawNode(const Node& node, sf::Color color);
    void drawEdge(const Node& a, const Node& b, int weight, sf::Color color, bool showWeight = true);
};
