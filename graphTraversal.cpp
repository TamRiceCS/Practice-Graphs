#include <iostream>
#include <vector>
#include <queue> 
#include <stack>
using namespace std;


/*
    How dijkstra works...
        load a vector of all nodes and have them equal to int_max
        pick a node to start nav at
        from that node update the to node IF curr node cost + edge is less than node's curr value
        mark node as visited
    
*/
void dijkstra(int given, vector<vector<int>> graph) {

    vector<int> visited(6,0);
    vector<int> distance(6, INT_MAX);
    queue<int> nav;
    nav.push(given);

    visited[given] = 1;
    distance[given] = 0;

    while(!nav.empty()) {
        for(int i = 0; i < 6; i++) {
            if(graph[nav.front()][i] != 0 && nav.front() != i) {
                if(distance[i] > graph[nav.front()][i] + distance[nav.front()]) {
                    distance[i] = graph[nav.front()][i] + distance[nav.front()];
                }
                if(visited[i] == 0) {
                    visited[i] = 1;
                    nav.push(i);
                }
            }
        }

        nav.pop();
    }

    for(int i = 0; i < 6; i++) {
        cout << i << "\'s min distance is: " << distance[i] << endl;
    }
}

/*
    How kruskal works...
        sort all edges by weight
        chose the cheapest weight that connects an unvisited node
        keep adding cheap weights until all nodes are connected
*/
void kruskal() {

}

int main() {

    // Let's assume that if the value is 0, there is no path!
    vector<vector<int>> graph = {6, vector<int>(6, 0)};
    vector<int> visited(6,0);
    vector<int> distance(6, INT_MAX);

    // graph[from][to]
    graph[0][1] = 10;
    graph[0][2] = 10;
    graph[1][2] = 5;
    graph[1][3] = 5;
    graph[2][4] = 20;
    graph[4][3] = 20;
    graph[4][5] = 15;
    graph[3][5] = 15;

    dijkstra(0, graph);


    cout << "Let's run dijkstra's algotithm, it works for both directed and undirected." << endl;



}