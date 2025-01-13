//#include <iostream>
//#include <vector>
//using namespace std;
//
//
//class Graph {
//private:
//    int vertices;
//    bool isDirected;
//    vector<int>* adjacencyList;
//    int** adjacencyMatrix;      
//
//public:
//    Graph(int vertices, bool isDirected) : vertices(vertices), isDirected(isDirected)
//    {
//        adjacencyList = new vector<int>[vertices]; 
//
//        adjacencyMatrix = new int* [vertices];
//        
//        for (int i = 0; i < vertices; i++) {
//            adjacencyMatrix[i] = new int[vertices] {0};
//        }
//    }
//
//    ~Graph() {
//        delete[] adjacencyList; 
//
//        
//        for (int i = 0; i < vertices; i++) {
//            delete[] adjacencyMatrix[i];
//        }
//        delete[] adjacencyMatrix;
//    }
//
//    void addEdge(int u, int v) {
//        if (u < 0 || v < 0 || u >= vertices || v >= vertices)
//        {
//            cout << "Invalid edge: Vertices out of range." << endl;
//            return;
//        }
//
//        adjacencyList[u].push_back(v);
//        adjacencyMatrix[u][v] = 1;
//
//        if (!isDirected) {
//            adjacencyList[v].push_back(u);
//            adjacencyMatrix[v][u] = 1;
//        }
//    }
//
//    void displayAdjacencyList()
//    {
//        cout << "Adjacency List:" << endl;
//
//        for (int i = 0; i < vertices; i++) {
//            
//            cout << i << ": ";
//            
//            for (int neighbor : adjacencyList[i]) {
//                cout << neighbor << " ";
//            }
//            cout << endl;
//        }
//    }
//
//    void displayAdjacencyMatrix()
//    {
//        cout << "Adjacency Matrix:" << endl;
//        for (int i = 0; i < vertices; i++) {
//
//            for (int j = 0; j < vertices; j++) {
//                cout << adjacencyMatrix[i][j] << " ";
//            }
//            cout << endl;
//        }
//    }
//
//    void checkEdgeExistence(int u, int v)
//    {
//        if (u < 0 || v < 0 || u >= vertices || v >= vertices)
//        {
//            cout << "Invalid vertices: Out of range." << endl;
//            return;
//        }
//
//        if (adjacencyMatrix[u][v]) {
//            cout << "Edge exists between " << u << " and " << v << "." << endl;
//        }
//        else {
//            cout << "No edge exists between " << u << " and " << v << "." << endl;
//        }
//    }
//};
//
//void main() {
//    int vertices, edges;
//    bool isDirected;
//
//    cout << "Enter the number of vertices: ";
//    cin >> vertices;
//
//    cout << "Enter the number of edges: ";
//    cin >> edges;
//
//    cout << "Is the graph directed? (1 for Yes, 0 for No): ";
//    cin >> isDirected;
//
//    Graph graph(vertices, isDirected);
//
//    cout << "Enter edges u,v:" << endl;
//    for (int i = 0; i < edges; i++) {
//        int u, v;
//        cin >> u >> v;
//        graph.addEdge(u, v);
//    }
//
//    cout << endl;
//    graph.displayAdjacencyList();
//
//    cout << endl;
//    graph.displayAdjacencyMatrix();
//
//    cout << "\nChecking edge existence between two vertices:" << endl;
//    cout << "Enter vertices (u,v): ";
//    int u, v;
//    cin >> u >> v;
//    graph.checkEdgeExistence(u, v);
//
//
//    cout << "\n";
//    system("pause");
//}