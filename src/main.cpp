#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Dijkstra.h"
#include "Visualizer.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 650), "NetRoute - Network Routing Simulator");
    window.setFramerateLimit(60);

    // Build the network
    Graph graph;
    graph.addNode("R-A",  150, 150);
    graph.addNode("R-B",  400, 100);
    graph.addNode("R-C",  700, 200);
    graph.addNode("R-D",  250, 350);
    graph.addNode("R-E",  550, 400);
    graph.addNode("R-F",  750, 500);

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 3, 2);
    graph.addEdge(1, 2, 5);
    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 3);
    graph.addEdge(2, 4, 2);
    graph.addEdge(2, 5, 6);
    graph.addEdge(3, 4, 8);
    graph.addEdge(4, 5, 1);

    Visualizer viz(window);

    // Find shortest path from R-A (0) to R-F (5)
    std::vector<int> path = Dijkstra::findPath(graph, 0, 5);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color(20, 20, 30));
        viz.drawGraph(graph);
        viz.drawPath(graph, path);
        window.display();
    }

    return 0;
}