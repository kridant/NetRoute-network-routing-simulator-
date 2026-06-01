#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Dijkstra.h"
#include "Visualizer.h"
#include <cmath>

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

    int src = -1, dest = -1;
    std::vector<int> path;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse click
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {

                float mx = event.mouseButton.x;
                float my = event.mouseButton.y;

                // Check if click is near any node
                for (int i = 0; i < graph.nodeCount(); i++) {
                    float dx = graph.nodes[i].x - mx;
                    float dy = graph.nodes[i].y - my;
                    float dist = std::sqrt(dx*dx + dy*dy);

                    if (dist < 25) {  // clicked within node radius
                        if (src == -1) {
                            // First click — set source
                            src = i;
                            path.clear();
                        } else if (dest == -1 && i != src) {
                            // Second click — set destination, run Dijkstra
                            dest = i;
                            path = Dijkstra::findPath(graph, src, dest);
                        } else {
                            // Third click — reset
                            src = i;
                            dest = -1;
                            path.clear();
                        }
                        break;
                    }
                }
            }
        }

        window.clear(sf::Color(20, 20, 30));
        viz.drawGraph(graph);
        viz.drawPath(graph, path);
        viz.drawSelection(graph, src, dest);
        viz.drawInfo(graph, path, src, dest);
        window.display();
    }

    return 0;
}