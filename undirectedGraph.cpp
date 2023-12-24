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

bool detectCycle(node* curr, node* parent, vector<int>& visited, bool& cycle) {
    
    if(cycle == true) {
        return cycle;
    }

    visited[curr->value] = 1;

    for(auto n : curr->neighbors) {
        if(visited[n->value] == 1 && n != parent) {
            cycle = true;
            break;
        }
        if(visited[n->value] == 0) {
            detectCycle(n, curr, visited, cycle);
        }
    }


    return cycle;
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
    bool fact = false;
    bool found = detectCycle(groundzero, nullptr, cycle0, fact);
    cout << "Cycle Found: " << found << endl;

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
    fact = false;
    found = detectCycle(groundzero, nullptr, cycle1, fact);
    cout << "Cycle Found: " << found << endl;

    node* t1 = new node(0);
    node* t2 = new node(1);
    node* t3 = new node(2);
    node* t4 = new node(3);
    node* t5 = new node(4);

    t1->neighbors.push_back(t2);
    t2->neighbors.push_back(t1);
    t2->neighbors.push_back(t3);
    t2->neighbors.push_back(t4);
    t2->neighbors.push_back(t5);
    t3->neighbors.push_back(t2);
    t4->neighbors.push_back(t2);
    t5->neighbors.push_back(t2);



    cout << "\nLet's try to find cycle points" << endl;
    vector<int> cycle2(5,0);
    fact = false;
    found = detectCycle(t1, nullptr, cycle2, fact);
    cout << "Cycle Found: " << found << endl;

    cout << "\n Can not do topological sorting due to it needing to test DAGS which are directed!" << endl;


}