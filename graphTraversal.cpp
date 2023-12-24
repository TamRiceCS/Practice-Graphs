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
        pick a node
        connect the min node that reaches out
        keep picking min node w/i network that connects an unvisited node

*/

bool helperP(pair<int,int> a, pair<int,int> b) {
    return a.second < b.second;
}

void prim(int start, vector<vector<pair<int,int>>> aj) {
    set<int> visited;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minPQ;
    minPQ.push(make_pair(0, start)); // weight, node

    vector<pair<int,int>> mst;

    while(visited.size() != aj.size()) {
        pair<int,int> temp = minPQ.top();
        minPQ.pop();
        if(visited.find(temp.second) != visited.end()) {
            continue;
        }

        visited.insert(temp.second);
        mst.push_back(make_pair(temp.second, temp.first));

        for(int i = 0; i < aj[temp.second].size(); i++) {
            if(visited.find(aj[temp.second][i].first) == visited.end()) {
                minPQ.push(make_pair(aj[temp.second][i].second, aj[temp.second][i].first));
            }
        }

    }

    for(auto elem : mst) {
        cout << "Chose at node (" << elem.first << ") of weight: " << elem.second << " to include in the MST" << endl;
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

    vector<vector<pair<int,int>>> aj (6, vector<pair<int,int>>());

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