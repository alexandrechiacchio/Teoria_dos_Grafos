#include <bits/stdc++.h>
#include "ABSadj.cpp"
using namespace std;

class Graph {
    int nodesCnt = 0;
    int edgesCnt = 0;
    vector<bool> visited;
    vector<int> depth;
    vector<int> parent;
    vector<int> component;
    AbstractAdj* adj;
    string inputFile;

    int componentCnt = 0;

public:

    Graph(Adjecencytype type , string filename) {
        inputFile = filename;

        ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        file >> nodesCnt;
        visited.resize(nodesCnt + 1 , false);
        depth.resize(nodesCnt + 1 , 0);
        parent.resize(nodesCnt + 1 , 0);
        component.resize(nodesCnt + 1 , 0);

        if (type == vector_t) {
            adj = new VectorAdj(nodesCnt);
        } else if (type == list_t) {
            adj = new ListAdj(nodesCnt);
        } else {
            adj = new MatrixAdj(nodesCnt);
        }

        while (!file.eof()) {
            edgesCnt++;
            int a , b;
            file >> a >> b;
            adj->addEdge(a , b);
        }

    }

    int size() {
        return edgesCnt;
    }

    int EdgeSize() {
        return adj->EdgeSize();
    }

    int degree(int u) {
        return adj->degree(u);
    }

    int maxDegree() {
        return adj->maxDegree();
    }

    int minDegree() {
        return adj->minDegree();
    }

    double avgDegree() {
        return adj->avgDegree();
    }

    int medianDegree() {
        return adj->medianDegree();
    }

    void reset() {
        componentCnt = 0;
        visited.resize(nodesCnt + 1 , false);
        depth.resize(nodesCnt + 1 , 0);
        parent.resize(nodesCnt + 1 , 0);
        component.resize(nodesCnt + 1 , 0);
    }


    int DFS(int u) {
        componentCnt++;
        stack<int> stack_graph;
        stack_graph.push(u);
        component[u] = componentCnt;
        parent[u] = u;
        while (!(stack_graph.empty())) {
            int v = stack_graph.top(); stack_graph.pop();
            if (visited[v] == false) {
                visited[v] = true;
                component[v] = componentCnt;
                depth[v] = depth[v] + 1;
                this->nodes[v]->setDepth(depth[v]);
                this->nodes[v]->setParent(parent[v]);
                for (int viz : adj->getAdj(v)) {
                    parent[viz] = v;
                    stack_graph.push(viz);
                }
            }
        }
        return count(visited.begin() , visited.end() , true);
    }

    int BFS(int u) {
        componentCnt++;
        vector<bool> visited(size() + 1 , false);
        queue<int> queue_graph;
        queue_graph.push(u);
        nodes[u]->setComponent(componentCnt);
        visited[u] = true;
        while (!(queue_graph.empty())) {
            int v = queue_graph.front(); queue_graph.pop();
            nodes[v]->setComponent(componentCnt);
            for (int viz : adj->getAdj(v)) {
                if (visited[viz] == false) {
                    queue_graph.push(viz);
                    visited[viz] = true;
                    nodes[viz]->visit();
                    nodes[viz]->setParent(v);
                    nodes[viz]->setDepth(nodes[v]->getDepth() + 1);
                }
            }
        }
        return count(visited.begin() , visited.end() , true);
    }

    // average time in seconds to run DFS 100 times
    double timeDFS() {
        clock_t start , end;
        srand(clock());
        for (int i = 0; i < 100; i++)
            reset();
        start = clock();
        DFS(((rand() % size()) + 1) % size());
        end = clock();
        return (double)(end - start) / CLOCKS_PER_SEC;
    }

    // average time in seconds to run BFS 100 times
    double timeBFS() {
        srand(clock());
        clock_t start , end;
        for (int i = 0; i < 100; i++)
            reset();
        start = clock();
        BFS(((rand() % size()) + 1) % size());
        end = clock();
        return (double)(end - start) / CLOCKS_PER_SEC;
    }

    vector<vector<int>> FloydWarshall() {
        cout << "Running Floyd Warshall\r";
        vector<vector<int>> dist(size() + 1 , vector<int>(size() + 1 , size() + 10));
        for (int i = 1; i <= size(); i++) {
            vector<int> aux = adj->getAdj(i);
            for (int j = 0; j < aux.size(); j++) {
                dist[i][aux[j]] = 1;
            }
        }
        for (int i = 0; i <= size(); i++) {
            dist[i][i] = 0;
        }
        for (int k = 1; k <= size(); k++) {
            for (int i = 1; i <= size(); i++) {
                for (int j = 1; j <= size(); j++) {
                    if (i != j && i != k && j != k) {
                        dist[i][j] = min(dist[i][j] , dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        return dist;
    }

    int diameter(int tol = 1e4) {
        cout << "Finding Diameter\r\n";
        int diameter = -1;
        reset();
        for (int i = 1; i <= size() && i <= tol; i++) {
            BFS(i);
            for (int i = 1; i <= size(); i++) {
                if (nodes[i]->getDepth() > diameter) {
                    diameter = nodes[i]->getDepth();
                }
            }
        }
        return diameter;
    }
}