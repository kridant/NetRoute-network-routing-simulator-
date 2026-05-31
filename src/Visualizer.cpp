#include "Visualizer.h"
#include <iostream>
#include <string>

namespace {

bool loadFont(sf::Font& font) {
    const char* paths[] = {
        "assets/OpenSans.ttf",
        "../assets/OpenSans.ttf",
#ifdef NETROUTE_ASSETS_DIR
        NETROUTE_ASSETS_DIR "/OpenSans.ttf",
#endif
    };
    for (const char* path : paths) {
        if (font.loadFromFile(path))
            return true;
    }
    return false;
}

bool isValidIndex(const Graph& graph, int idx) {
    return idx >= 0 && idx < graph.nodeCount();
}

} // namespace

Visualizer::Visualizer(sf::RenderWindow& win) : window(win) {
    fontLoaded = loadFont(font);
    if (!fontLoaded)
        std::cerr << "ERROR: Could not load font (tried assets/OpenSans.ttf)\n";
}

void Visualizer::drawNode(const Node& node, sf::Color color) {
    sf::CircleShape circle(22);
    circle.setFillColor(color);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(2);
    circle.setPosition(node.x - 22, node.y - 22);
    window.draw(circle);

    if (!fontLoaded)
        return;

    sf::Text label;
    label.setFont(font);
    label.setString(node.name);
    label.setCharacterSize(13);
    label.setFillColor(sf::Color::White);
    label.setPosition(node.x - 18, node.y - 10);
    window.draw(label);
}

void Visualizer::drawEdge(const Node& a, const Node& b, int weight, sf::Color color, bool showWeight) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(a.x, a.y), color),
        sf::Vertex(sf::Vector2f(b.x, b.y), color)
    };
    window.draw(line, 2, sf::Lines);

    if (!fontLoaded || !showWeight)
        return;

    sf::Text wLabel;
    wLabel.setFont(font);
    wLabel.setString(std::to_string(weight));
    wLabel.setCharacterSize(12);
    wLabel.setFillColor(sf::Color::Yellow);
    wLabel.setPosition((a.x + b.x) / 2, (a.y + b.y) / 2);
    window.draw(wLabel);
}

void Visualizer::drawGraph(const Graph& graph) {
    for (int u = 0; u < graph.nodeCount(); u++) {
        for (const Edge& e : graph.adjList[u]) {
            if (e.to > u) {
                drawEdge(graph.nodes[u], graph.nodes[e.to],
                         e.weight, sf::Color(100, 100, 100));
            }
        }
    }
    for (const Node& node : graph.nodes)
        drawNode(node, sf::Color(50, 100, 200));
}

void Visualizer::drawPath(const Graph& graph, const std::vector<int>& path) {
    if (path.size() < 2)
        return;

    for (int idx : path) {
        if (!isValidIndex(graph, idx))
            return;
    }

    for (int i = 0; i < static_cast<int>(path.size()) - 1; i++) {
        drawEdge(graph.nodes[path[i]], graph.nodes[path[i + 1]],
                 0, sf::Color::Green, false);
    }
    for (int idx : path)
        drawNode(graph.nodes[idx], sf::Color(255, 140, 0));
}
