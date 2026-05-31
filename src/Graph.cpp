#include "Graph.h"

void Graph:: addNode(const std:: string & name ,float x , float y ){
        nodes.push_back({name , x , y}); 
        adjList.push_back({});
}

void Graph:: addEdge(int from , int to , int weight){
    adjList[from].push_back({to, weight}); 
    adjList[to].push_back({from, weight}); 
}

int Graph::nodeCount()const{
    return nodes.size(); 
}

