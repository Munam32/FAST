#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int vertices;
    vector<vector<int>> adjacencyList;

public:
    Graph(int vertices) : vertices(vertices) {
        adjacencyList.resize(vertices);
    }

    void addEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= vertices || v >= vertices) {
            cout << "Invalid edge: vertices out of range." << endl;
            return;
        }
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); 
    }

    void BFS(int start, vector<bool>& visited) {
        queue<int> q;
        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal starting from vertex " << start << ": ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            for (int neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    bool isConnected() {
        vector<bool> visited(vertices, false);
        BFS(0, visited);

        for (bool v : visited) {
            if (!v) 
             return false;
        }
        return true;
    }

    int countConnectedComponents() {
        vector<bool> visited(vertices, false);
        int componentCount = 0;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                componentCount++;
                BFS(i, visited);
            }
        }

        return componentCount;
    }
};

void inputGraph(Graph& graph, int edges) {
    cout << "Enter edges (u v format):" << endl;
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }
}

int main() {
    int vertices, edges;

    cout << "Enter the number of vertices: ";
    cin >> vertices;

    cout << "Enter the number of edges: ";
    cin >> edges;

    Graph graph(vertices);
    inputGraph(graph, edges);

    cout << endl;

    // Perform BFS traversal from a user-specified starting vertex
    int startVertex;
    cout << "Enter the starting vertex for BFS: ";
    cin >> startVertex;

    if (startVertex < 0 || startVertex >= vertices) {
        cout << "Invalid starting vertex!" << endl;
        return 1;
    }

    vector<bool> visited(vertices, false);
    graph.BFS(startVertex, visited);

    
    cout << endl;
    if (graph.isConnected()) {
        cout << "The graph is connected." << endl;
    }
    else {
        cout << "The graph is not connected." << endl;
    }


    int connectedComponents = graph.countConnectedComponents();
    cout << "Number of connected components: " << connectedComponents << endl;

    system("pause");
    return 0;
}