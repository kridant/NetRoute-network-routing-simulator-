# include "Dijkstra.h"
# include <queue>
# include <vector> 
# include <climits>

std:: vector<int> Dijkstra::findPath(const Graph& graph , int src , int dest){
        int n = graph.nodeCount(); 
        std:: vector<int>dist(n ,INT_MAX);// dist[i] = shortest known distance from src to node i
        std:: vector<int>prev (n , -1); // prev[i] = which node we came from to reach node i
        std:: priority_queue<std:: pair<int ,int>, std:: vector<std:: pair<int, int>> , std::greater<> >pq ; 
        dist [src]=0 ; 
        pq.push({0, src}); 
        while (!pq.empty()){
            auto [d,u]= pq.top() ; pq.pop(); 
            if (d> dist[u])continue ; // skip if we laready find a better path 

            if (u==dest)break ; //stop early if we reached destination 


            for (const Edge& edge : graph.adjList[u]) {
                int v = edge.to;
                int newDist = dist[u] + edge.weight;

                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    pq.push({newDist, v});
                }
            }
        }
        std:: vector<int> path ; 
        if (dist[dest]==INT_MAX)return path ; 
        
        for ( int curr = dest ; curr!=-1 ; curr = prev[curr]){
                path.push_back(curr);
        }return path ; 
        
}
