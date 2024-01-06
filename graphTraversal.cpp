#include <iostream>
#include <vector>
#include <queue> 
#include <stack>
#include <algorithm>
#include <set>
using namespace std;


/*
    How dijkstra works...
        load a vector of all nodes and have them equal to int_max
        pick a node to start nav at
        from that node update the to node IF curr node cost + edge is less than node's curr value
        mark node as visited
    
*/
void dijkstra(int given, vector<vector<int>> graph) {

    vector<int> visited(graph.size(), 0);
    vector<int> distance(graph.size(), INT_MAX);
    queue<int> nav;
    nav.push(given);
    distance[given] = 0;

    while(!nav.empty()) {
        visited[nav.front()] = 1;
        for(int i = 0; i < graph.size(); i++) {
            if(nav.front() != i && graph[nav.front()][i] != 0) {
                if(distance[i] > distance[nav.front()] + graph[nav.front()][i]) {
                    distance[i] = distance[nav.front()] + graph[nav.front()][i];
                }
                if(visited[i] != 1) {
                    nav.push(i);
                }

            }
        }
        nav.pop();
    }

    for(int i = 0; i < distance.size(); i++) {
        cout << i << "\'s min distance is... " << distance[i] << endl;
    }
   
}

/*
    How kruskal works...
        sort all edges by weight
        chose the cheapest weight that connects an unvisited node
        keep adding cheap weights until all nodes are connected
*/

// This is so we can properly sort the edges by cheapest
bool helpK(vector<int> a, vector<int> b){
    return a[2] < b[2];
}

void kruskal(int numNodes, vector<vector<int>> edges) {
    
    sort(edges.begin(), edges.end(), helpK);
    vector<int> visited(numNodes, 0);
    vector<vector<int>> mst;

    for(int i = 0; i < edges.size(); i++) {
        if(visited[edges[i][0]] == 0 || visited[edges[i][1]] == 0) {
            visited[edges[i][0]] = 1;
            visited[edges[i][1]] = 1;
            mst.push_back(edges[i]);
        }
    }

    for(auto elem : mst) {
        cout << "Edge selected from " << elem[0] << " to " << elem[1]  << " with a weight of " << elem[2] << endl;
    }

}

/*
    How Prim's works
        pick a node w/ min weight (or start at source node)
        include node in mst
        update all other node distances from that node
        repeat until all nodes are included

*/


void prim(int start, vector<vector<pair<int,int>>> aj) {

    // aj is of the format aj[orginNode] = {end, weight}

    set<int> visited; // nodes we have visited
    vector<int> mst(aj.size(), INT_MAX); // mst[node] = weight
    int curr = start; // node we are iter through
    int min = start; // node that is the curr min node val that isn't in set
    mst[start] = 0;


    while(visited.size() != aj.size()) {
        visited.insert(min);

        for(int i = 0; i < aj[min].size(); i++) {
            // if the min exploritory edge is less than the recorded prior edges
            int newWeight = aj[min][i].second;
            int toNode = aj[min][i].first;
            int oldWeight = mst[toNode];

            if(newWeight < oldWeight) {
                mst[toNode] = aj[min][i].second;
            }
        }

        // find the min of the visited that is not in the set
        for(int i = 0; i < mst.size(); i++) {
            // guarantee we take some value
            if(min == curr && visited.find(i) == visited.end()) {
                min = i;
            }
            else if(mst[i] < mst[min] && visited.find(i) == visited.end()) {
                min = i;
            }
        }
        
        curr = min;

    }

    for(int i = 0; i < mst.size(); i++) {
        cout << "Node " << i << " added to MST w/ a weight of " << mst[i] << endl;
    }


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

    cout << "\nLet's run dijkstra's algotithm, it works for both directed and undirected." << endl;
    dijkstra(0, graph);

    vector<vector<int>> edges;
    // assume edges go both ways! c:
    edges.push_back({0,1,10});
    edges.push_back({0,2,10});
    edges.push_back({1,3,5});
    edges.push_back({1,2,5});
    edges.push_back({2,4,20});
    edges.push_back({3,5,15});
    edges.push_back({4,3,20});
    edges.push_back({4,5,15});

    cout << "\nLet's run kruskal's algotithm, it works for undirected. PRODUCES MST" << endl;
    kruskal(6, edges);

    vector<vector<pair<int,int>>> aj (5, vector<pair<int,int>>());

    aj[0].push_back(make_pair(1,10));
    aj[0].push_back(make_pair(2,10));
    aj[1].push_back(make_pair(3,5));
    aj[1].push_back(make_pair(2,5));
    aj[2].push_back(make_pair(4,20));
    aj[3].push_back(make_pair(5,15));
    aj[4].push_back(make_pair(3,20));
    aj[4].push_back(make_pair(5,15));

    cout << "\nLet's run prim's algotithm, it works for undirected. PRODUCES MST" << endl;

    prim(0, aj);


}