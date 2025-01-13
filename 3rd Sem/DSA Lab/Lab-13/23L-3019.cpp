#include <iostream>
#include <vector>
using namespace std;


void validate();



void inputGraph(int N, int E, vector<vector<int>>& adjList) {
    adjList.resize(N);
    for (int i = 0; i < E; i++) {

        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Since the graph is undirected
    }
}

// Recursive DFS function
void DFS(int node, vector<bool>& visited, vector<int>& order, vector<vector<int>>& adjList) {
    visited[node] = true;
    order.push_back(node);

    for (int neighbor : adjList[node]) {
        if (!visited[neighbor]) {
            DFS(neighbor, visited, order, adjList);
        }
    }
}

// Function to display the DFS traversal order
void displayOrder(const vector<int>& order) {
    for (int node : order) {
        cout << node << " ";
    }
    cout << endl;
}

// Function to check if the graph is connected
bool isConnected(vector<vector<int>>& adjList, int N) {
    vector<bool> visited(N, false);
    vector<int> order;

    DFS(0, visited, order, adjList); // Start DFS from node 0

    for (bool visit : visited) {
        if (!visit) return false; // If any node is not visited, the graph is not connected
    }
    return true;
}

// Function to count the number of connected components
int countComponents(vector<vector<int>>& adjList, int N) {
    vector<bool> visited(N, false);
    int componentCount = 0;

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            vector<int> order;
            DFS(i, visited, order, adjList);
            componentCount++;
        }
    }
    return componentCount;
}

// Main function
void main() {
    int N, E;
    cout << "Enter number of vertices: ";
    cin >> N;
    cout << "Enter number of Edges: ";
    cin >> E;

    vector<vector<int>> adjList;
    inputGraph(N, E, adjList);

    vector<bool> visited(N, false);
    vector<int> order;

    cout << "DFS Traversal: ";
    DFS(0, visited, order, adjList);
    displayOrder(order);

    if (isConnected(adjList, N)) {
        cout << "The graph is connected." << endl;
       
    }
    else {
        cout << "The graph is not connected." << endl;
        cout << "Number of connected components: " << countComponents(adjList, N) << endl;
        
    }

    system("pause");
}