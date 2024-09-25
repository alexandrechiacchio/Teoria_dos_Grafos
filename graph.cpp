#include <bits/stdc++.h>
#include "ABSadj.cpp"
#include <sys/resource.h>
#include <ctime>
#include <cstdlib>

using namespace std;

class Graph {
    int nodesCnt = 0;
    int edgesCnt = 0;
    vector<bool> visited;
    vector<int> depth;
    vector<int> parent;
    vector<int> component;
    AbstractAdj* adj;
    Adjecencytype type;
    string inputFile;

    int componentCnt = 0;

public:

    Graph(Adjecencytype _type , string filename) {
        inputFile = filename;
        type = _type;

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
        return nodesCnt;
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
        visited.clear();
        depth.clear();
        parent.clear();
        component.clear();
        visited.resize(nodesCnt + 1 , false);
        depth.resize(nodesCnt + 1 , -1);
        parent.resize(nodesCnt + 1 , -1);
        component.resize(nodesCnt + 1 , 0);
    }


    void DFS(int u) {
        componentCnt++;
        stack<int> stck;

        stck.push(u);
        component[u] = componentCnt;
        parent[u] = u;
        depth[u] = 0;
        while (!(stck.empty())) {
            int v = stck.top();
            stck.pop();
            if (visited[v] == false) {
                visited[v] = true;
                component[v] = componentCnt;
                for (int viz : adj->getAdj(v)) {
                    if (visited[viz] == false) {
                        parent[viz] = v;
                        depth[viz] = depth[v] + 1;
                        stck.push(viz);
                    }
                }
            }
        }
    }

    void BFS(int u) {
        componentCnt++;
        queue<int> queue;
        queue.push(u);
        component[u] = componentCnt;
        visited[u] = true;
        depth[u] = 0;
        parent[u] = u;
        while (!(queue.empty())) {
            u = queue.front(); queue.pop();
            for (int v : adj->getAdj(u)) {
                if (!visited[v]) {
                    queue.push(v);
                    visited[v] = true;
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    component[v] = componentCnt;
                }
            }
        }
    }

    // average time in seconds to run DFS 100 times
    double timeDFS() {
        clock_t start , end;
        srand(clock());
        for (int i = 0; i < 100; i++) {
            reset();
            start = clock();
            DFS(((rand() % size()) + 1));
            end = clock();
        }
        return (double)(end - start) / CLOCKS_PER_SEC;
    }

    // average time in seconds to run BFS 100 times
    double timeBFS() {
        clock_t start , end;
        srand(clock());
        for (int i = 0; i < 100; i++) {
            reset();
            start = clock();
            BFS(((rand() % size()) + 1));
            end = clock();
        }
        return (double)(end - start) / CLOCKS_PER_SEC;
    }

    vector<vector<int>> FloydWarshall() {
        cout << "Running Floyd Warshall" << endl;
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
        for (int i = 1; i <= size() && i <= tol; i++) {
            reset();
            BFS(i);
            for (int i = 1; i <= size(); i++) {
                diameter = max(diameter , depth[i]);
            }
        }
        return diameter;
    }

    vector<vector<int>> getComponents(){
        reset();
        for(int i = 1; i<=size(); i++){
            if(visited[i] == false){
                BFS(i);
            }
        }

        vector<vector<int>> ret(*max_element(component.begin(), component.end()) + 1);

        for(int i = 1; i<=size(); i++){
            ret[component[i]].push_back(i);
        }

        sort(ret.begin(), ret.end(), [](vector<int> a, vector<int> b){
            return a.size() > b.size();
        });

        return ret;
    }


    int minComponentSize(){
        vector<vector<int>> components = getComponents();
        return min_element(components.begin(), components.end()-1, [](vector<int> a, vector<int> b){
            return a.size() < b.size();
        })->size();
    }

    int maxComponentSize(){
        vector<vector<int>> components = getComponents();
        return max_element(components.begin(), components.end()-1, [](vector<int> a, vector<int> b){
            return a.size() < b.size();
        })->size();
    }

    int componentsCnt(){
        vector<vector<int>> components = getComponents();
        return components.size()-1; // components.back() does not count as its empty
    }

    void printInfo2file() {
        string outputFileName = "output_" + to_string((int)type) + "_" + inputFile;
        ofstream file(outputFileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << "output.txt" << std::endl;
            return;
        }
        cout << "printing general info: " << outputFileName << endl;
        file << "Number of nodes: " << size() << endl;
        file << "Number of edges: " << EdgeSize() << endl;
        file << "Max degree: " << maxDegree() << endl;
        file << "Min degree: " << minDegree() << endl;
        file << "Avg degree: " << avgDegree() << endl;
        file << "Median degree: " << medianDegree() << endl;
        struct rusage usage;
        if (getrusage(RUSAGE_SELF , &usage) < 0) {
            cerr << "Error getting resource usage" << endl;
            return;
        }
        file << "Memory usage: " << (double(usage.ru_maxrss) / 1024.0) << "MB" << endl;

        cout << "printing time info: " << endl;
        file << "Time DFS: " << timeDFS() << "s" << endl;
        file << "Time BFS: " << timeBFS() << "s" << endl;

        if(type != vector_t) return; // tudo igual daqui pra baixo, mas muito demorado se n for por vetor

        cout << "printing nodes info: " << endl;
        for (int i = 1; i <= 3; i++) {
            file << "DFS(" << i << ")" << endl;
            reset();
            DFS(i);
            file << "parent[10] = " << parent[10] << endl;
            file << "parent[20] = " << parent[20] << endl;
            file << "parent[30] = " << parent[30] << endl;
        }

        for (int i = 1; i <= 3; i++) {
            file << "BFS(" << i << ")" << endl;
            reset();
            BFS(i);
            file << "parent[10] = " << parent[10] << endl;
            file << "parent[20] = " << parent[20] << endl;
            file << "parent[30] = " << parent[30] << endl;
        }

        reset();
        BFS(10);
        file << "Distance between 10 and 20: " << depth[20] << endl;
        file << "Distance between 10 and 30: " << depth[30] << endl;
        reset();
        BFS(20);
        file << "Distance between 20 and 30: " << depth[30] << endl;

        cout << "printing connected components info: " << endl;

        vector<vector<int>> components = getComponents();
        int minComponentSize = (min_element(components.begin(), components.end()-1, [](vector<int> a, vector<int> b){
            return a.size() < b.size();
        }))->size();
        int maxComponentSize = (max_element(components.begin(), components.end()-1, [](vector<int> a, vector<int> b){
            return a.size() < b.size();
        }))->size();

        file << "Número de componentes conexas: " << components.size()-1 << endl;
        file << "Tamanho da menor componente: " << minComponentSize << endl;
        file << "Tamanho da maior componente: " << maxComponentSize << endl;

        cout << "printing Diameter info: " << endl;
        file << "Diameter: " << diameter() << endl;

        cout << "printing components: " << endl;

        for(int i = 0; i<components.size()-1; i++){
            file << "Component " << i+1 << " size: " << components[i].size() << endl;
            for(int j = 0; j<components[i].size(); j++){
                file << components[i][j] << " ";
            }
            file << '\n' << endl;
        }


    }
};