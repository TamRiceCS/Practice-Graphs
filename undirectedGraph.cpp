#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class node {
    public:
        int value = 0;
        vector<node*> neighbors;

        node(int v) {
            value = v;
        }

        node(int v, int w) {
            value = v;
        }

        node(int v, int w, vector<node*> n) {
            value = v;
            neighbors = n;
        }
};

void bfs(node* start){

    if(start == nullptr) {
        return;
    }

    vector<int> visited(6,0);
    queue<node*> nav;
    nav.push(start);
    visited[start->value] = 1;
    cout << "\nStarting graph BFS navigation at: " << start->value << endl;

    while(!nav.empty()) {
        for(auto elem : nav.front()->neighbors) {
            if(visited[elem->value] == 0) {
                visited[elem->value] = 1;
                cout << "Just visited node: " << elem->value << endl;
                nav.push(elem);
            }
        }
        nav.pop();
    }

}

void recursiveDFS(node* start, vector<int>& visited) {
    if(visited[start->value] == 1) {
        return;
    }

    visited[start->value] = 1;
    cout << "Just visited node: " << start->value << endl;

    for(auto elem : start->neighbors) {
        recursiveDFS(elem, visited);
    }

}

// detect a cycle
// iter through dfs remembering the prior parent
// if node connects to an already visited node that isn't the prior node, a cycle was made.

void detectCycle(node* curr, node* parent, vector<int>& visited) {
    if(visited[curr->value] == 1) {
        return;
    }

    visited[curr->value] = 1;

    for(auto elem : curr->neighbors) {
        if(parent != nullptr && elem != parent) {
            if(visited[elem->value] == 1) {
                cout << "CYCLE CYCLE CYCLE " << elem->value << " and " << curr->value << endl;
                return;
            }
            else{
            cout << "NO cycle " << elem->value << " and " << curr->value << endl;
            }
        }
        detectCycle(elem, curr, visited);
    }
}



int main() {
    cout << "\nThere are many ways to implement a graph, adjacency matrix and adjacency list" << endl;
    cout << "This is basically using a 2D Array or a 2D matrix that does not include non-neighboring nodes" << endl;
    cout << "We will be using the more efficient implementation, there is very little alg implementation difference between the two" << endl;

    node* groundzero = new node(0);
    node* one = new node(1);
    node* two = new node(2);
    node* three = new node(3);
    node* four = new node(4);
    node* five = new node(5);

    groundzero->neighbors.push_back(one);
    groundzero->neighbors.push_back(two);
    one->neighbors.push_back(groundzero);
    one->neighbors.push_back(two);
    one->neighbors.push_back(three);
    two->neighbors.push_back(groundzero);
    two->neighbors.push_back(one);
    two->neighbors.push_back(four);
    three->neighbors.push_back(one);
    three->neighbors.push_back(four);
    three->neighbors.push_back(five);
    four->neighbors.push_back(two);
    four->neighbors.push_back(three);
    four->neighbors.push_back(five);
    five->neighbors.push_back(three);
    five->neighbors.push_back(four);

    bfs(groundzero);

    vector<int> recDFS(6,0);

    cout << "\nRecursive DFS" << endl;
    recursiveDFS(groundzero, recDFS);

    cout << "\nLet's try to find cycle points" << endl;
    vector<int> cycle0(6,0);
    detectCycle(groundzero, nullptr, cycle0);

    node* n0 = new node(0);
    node* n1 = new node(1);
    node* n2 = new node(2);

    n0->neighbors.push_back(n1);
    n0->neighbors.push_back(n2);
    n1->neighbors.push_back(n0);
    n1->neighbors.push_back(n2);
    n2->neighbors.push_back(n0);
    n2->neighbors.push_back(n1);


    cout << "\nLet's try to find cycle points" << endl;
    vector<int> cycle1(3,0);
    detectCycle(n0, nullptr, cycle1);

    cout << "\n Can not do topological sorting due to it needing to test DAGS which are directed!" << endl;


}