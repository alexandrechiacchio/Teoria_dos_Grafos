#include <bits/stdc++.h>
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
    vector<vector<pair<int , int>>> adj;
    vector<vector<pair<int , int>>> flow;
    string inputFile;
    vector<int> dist;


    int componentCnt = 0;

    bool containsNegativeWeight = false;

public:

    Graph(string filename) {
        inputFile = filename;
        cout << "Reading file " << filename << endl;
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
        adj.resize(nodesCnt + 1 , vector<pair<int , int>>());
        dist.resize(nodesCnt + 1 , 1e9);

        while (!file.eof()) {
            cout << "Reading file: " << edgesCnt << " lines read" << '\r';
            edgesCnt++;
            int a , b;
            int c;
            file >> a >> b >> c;
            // cout << a << " " << b << " " << c << '\n';
            adj[a].push_back({ b, c });
            // adj[b].insert({ a, c });
            if (c < 0) containsNegativeWeight = true;
        }
        cout << "\r\033[K" << "File read! " << edgesCnt << " lines read." << endl;
        flow = adj;
        for (auto& vec : flow) {
            for (auto& p : vec) {
                p.second = 0;
            }
        }
    }

    Graph(Graph* _graph) {
        inputFile = _graph->inputFile;
        cout << "Copying graph with input file " << _graph->inputFile << endl;
        nodesCnt = _graph->nodesCnt;
        edgesCnt = _graph->edgesCnt;
        visited = _graph->visited;
        depth = _graph->depth;
        parent = _graph->parent;
        component = _graph->component;
        adj = _graph->adj;
        dist = _graph->dist;
        containsNegativeWeight = _graph->containsNegativeWeight;
        flow = _graph->flow;
        cout << "Graph copied!" << endl;
    }

    int size() {
        return nodesCnt;
    }

    int EdgeSize() {
        return edgesCnt;
    }

    int degree(int u) {
        return adj[u].size();
    }

    int maxDegree() {
        return max(adj.begin() , adj.end() , [](vector<vector<pair<int , int>>>::iterator a , vector<vector<pair<int , int>>>::iterator b) {
            return a->size() < b->size();
            })->size();
    }

    int minDegree() {
        return min(adj.begin() , adj.end() , [](vector<vector<pair<int , int>>>::iterator a , vector<vector<pair<int , int>>>::iterator b) {
            return a->size() < b->size();
            })->size();
    }

    double avgDegree() {
        return (double)(2 * edgesCnt) / size();
    }

    int medianDegree() {
        return adj[adj.size() / 2].size();
    }

    vector<int> getAdj(int u) {
        vector<int> ret;
        for (pair<int , int> it : adj[u]) {
            ret.push_back(it.first);
        }
        return ret;
    }

    int getDist(int u) {
        return dist[u];
    }

    // resets everything exept flow
    void reset() {

        componentCnt = 0;
        visited.clear();
        depth.clear();
        parent.clear();
        component.clear();
        dist.clear();
        visited.resize(nodesCnt + 1 , false);
        depth.resize(nodesCnt + 1 , -1);
        parent.resize(nodesCnt + 1 , -1);
        component.resize(nodesCnt + 1 , 0);
        dist.resize(nodesCnt + 1 , 1e9);
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
                for (pair<int , int> it : adj[v]) {
                    int viz = it.first;
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
            for (pair<int , int> it : adj[u]) {
                int v = it.first;
                if (!visited[v] && it.second > 0) {
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
        clock_t total = 0;
        for (int i = 0; i < 100; i++) {
            reset();
            start = clock();
            DFS(((rand() % size()) + 1));
            end = clock();
            total += (end - start);
        }
        return (double)(total) / CLOCKS_PER_SEC;
    }

    // average time in seconds to run BFS 100 times
    double timeBFS() {
        clock_t start , end;
        srand(clock());
        clock_t total = 0;
        for (int i = 0; i < 100; i++) {
            reset();
            start = clock();
            BFS(((rand() % size()) + 1));
            end = clock();
            total += (end - start);
        }
        return (double)(total) / CLOCKS_PER_SEC;
    }

    vector<vector<int>> FloydWarshall() {
        cout << "Running Floyd Warshall" << endl;
        vector<vector<int>> dist(size() + 1 , vector<int>(size() + 1 , size() + 10));
        for (int i = 1; i <= size(); i++) {
            vector<int> aux = getAdj(i);
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


    // returns the distance between u and v using dijkstra algorithm
    int dikjstra(int u , int v = 0) {
        componentCnt++;
        priority_queue<pair<int , int>> queue;

        // initializing parameters of first node
        queue.push({ 0, u });
        component[u] = componentCnt;
        visited[u] = true;
        depth[u] = 0;
        dist[u] = 0;
        parent[u] = u;
        while (!(queue.empty())) {
            pair<int , int> u = queue.top(); queue.pop();
            if (-u.first > dist[u.second]) continue; // skips node if current dist is less than the one in queue
            for (pair<int , int> it : adj[u.second]) {
                int v = it.first;
                if (dist[v] > dist[u.second] + it.second) { // updates parameters if new path is shorter
                    visited[v] = true;
                    parent[v] = u.second;
                    depth[v] = depth[u.second] + 1;
                    component[v] = componentCnt;
                    dist[v] = dist[u.second] + it.second;
                    queue.push({ -dist[v], v });
                }
            }
        }
        return dist[v];
    }

    // same as diskjstra but without using priority queue
    int dikjstraNoHeap(int u , int v = 0) {
        componentCnt++;
        vector<pair<int , int>> queue;
        queue.push_back({ 0, u });
        component[u] = componentCnt;
        visited[u] = true;
        depth[u] = 0;
        dist[u] = 0;
        parent[u] = u;
        while (!(queue.empty())) {
            auto it = min_element(queue.begin() , queue.end());
            pair<int , int> u = *it;
            queue.erase(it);
            if (u.first > dist[u.second]) continue;
            for (pair<int , int> it : adj[u.second]) {
                int v = it.first;
                if (dist[v] > dist[u.second] + it.second) {
                    visited[v] = true;
                    parent[v] = u.second;
                    depth[v] = depth[u.second] + 1;
                    component[v] = componentCnt;
                    dist[v] = dist[u.second] + it.second;
                    queue.push_back({ dist[v], v });
                }
            }
        }
        return dist[v];
    }

    int Ford_Fulkerson(int s , int t) {
        Graph* residual = new Graph(this);
        vector<vector<pair<int , int>>> flow = adj;
        for (auto it : flow) for (auto it2 : it) it2.second = 0;
        // vector<vector<pair<int, int>>> residual = this->adj;

        // cout << this->adj.size() << " " << residual->adj.size() << endl;
        for (int i = 0; i < adj.size(); i++) {
            for (int j = 0; j < adj[i].size(); j++) {
                residual->adj[j].push_back({ i, 0 });
            }
        }
        cout << "Running Ford Fulkerson" << endl;
        while (true) {
            residual->BFS(s);
            if(residual->visited[t] == false) break;
            vector<int> nodesPath = residual->getPath(t);
            vector<pair<int,int>> edgesPath;
            int bottleneck = 1e9;
            int cur = t, last = t;
            // cout << residual->parent[s] << endl;
            while(residual->parent[cur] != cur) {
                // cout << cur << " " << residual->parent[cur] << endl;
                cur = residual->parent[cur];
                edgesPath.push_back({last, cur});
                auto curEdge = find_if(residual->adj[cur].begin(), residual->adj[cur].end(), [last](const pair<int, int>& edge) {
                    return edge.first == last;
                });
                bottleneck = min(bottleneck, curEdge->second);
                last = cur;
            }
            // cout << "bottleneck: " << bottleneck << endl;
            // for(auto i : edgesPath) {
                // cout << "{" << i.first << ", " << i.second << "} ";
            // }
            // cout << '\n';
            edgesPath.push_back({last, cur});
            for(auto it : edgesPath) {
                // cout << "edge " << it.first << " " << it.second << '\n';
                auto aux = find_if(residual->adj[it.first].begin(), residual->adj[it.first].end(), [it](const pair<int, int>& edge) {
                    return edge.first == it.second;
                });
                // cout << "aux: " << aux->first << " " << aux->second << '\n';
                aux->second -= bottleneck;
                // cout << "aux: " << aux->first << " " << aux->second << '\n';
                aux = find_if(residual->adj[it.second].begin(), residual->adj[it.second].end(), [it](const pair<int, int>& edge) {
                    return edge.first == it.first;
                });
                // cout << "aux: " << aux->first << " " << aux->second << '\n';
                aux->second += bottleneck;
                // cout << "aux: " << aux->first << " " << aux->second << '\n';
                // falta atualizar o flow (não precisa pq o residuo menos capacidade é igual ao flow)
            }
            residual->reset();
        }

        for (int i = 0; i < adj.size(); i++) {
            for (int j = 0; j < adj[i].size(); j++) {
                flow[i][j].second = adj[i][j].second - residual->adj[i][j].second;
            }
        }

        int flowValue = 0;
        for(int i = 0; i<adj[s].size(); i++) {
            flowValue += flow[s][i].second;
        }
        return flowValue;

    }

    double timeDijkstra() {
        clock_t start , end;
        srand(clock());
        clock_t total = 0;
        for (int i = 0; i < 100; i++) {
            reset();
            start = clock();
            dikjstra(((rand() % size()) + 1));
            end = clock();
            cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << '\r';
            total += (end - start);
        }
        cout << "\r\033[K" << "Average time: " << (double)(end - start) / CLOCKS_PER_SEC / 100 << endl;
        return (double)(total) / CLOCKS_PER_SEC / 100;
    }

    double timeDijkstraNoHeap() {
        clock_t start , end;
        srand(clock());
        clock_t total = 0;
        for (int i = 0; i < 100; i++) {
            reset();
            start = clock();
            dikjstraNoHeap(((rand() % size()) + 1));
            end = clock();
            cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << '\r';
            total += (end - start);
        }
        cout << "\r\033[K" << "Average time: " << (double)(end - start) / CLOCKS_PER_SEC / 100 << endl;
        return (double)(total) / CLOCKS_PER_SEC / 100;
    }

    int diameter(int tol = 1e2) {
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

    vector<vector<int>> getComponents() {
        reset();
        for (int i = 1; i <= size(); i++) {
            if (visited[i] == false) {
                BFS(i);
            }
        }

        vector<vector<int>> ret(*max_element(component.begin() , component.end()) + 1);

        for (int i = 1; i <= size(); i++) {
            ret[component[i]].push_back(i);
        }

        sort(ret.begin() , ret.end() , [](vector<int> a , vector<int> b) {
            return a.size() > b.size();
            });

        return ret;
    }


    int minComponentSize() {
        vector<vector<int>> components = getComponents();
        return min_element(components.begin() , components.end() - 1 , [](vector<int> a , vector<int> b) {
            return a.size() < b.size();
            })->size();
    }

    int maxComponentSize() {
        vector<vector<int>> components = getComponents();
        return max_element(components.begin() , components.end() - 1 , [](vector<int> a , vector<int> b) {
            return a.size() < b.size();
            })->size();
    }

    int componentsCnt() {
        vector<vector<int>> components = getComponents();
        return components.size() - 1; // components.back() does not count as its empty
    }

    vector<int> getPath(int u) {
        vector<int> ret;
        if (parent[u] == -1) return ret;
        while (parent[u] != u) {
            ret.push_back(u);
            u = parent[u];
        }
        ret.push_back(u);
        reverse(ret.begin() , ret.end());
        return ret;
    }


    // função que imprime as informações do grafo pedidas pelo trabalho 1
    void printInfo2file_1() {
        string outputFileName = "output_" + inputFile;
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
        int minComponentSize = (min_element(components.begin() , components.end() - 1 , [](vector<int> a , vector<int> b) {
            return a.size() < b.size();
            }))->size();
        int maxComponentSize = (max_element(components.begin() , components.end() - 1 , [](vector<int> a , vector<int> b) {
            return a.size() < b.size();
            }))->size();

        file << "Número de componentes conexas: " << components.size() - 1 << endl;
        file << "Tamanho da menor componente: " << minComponentSize << endl;
        file << "Tamanho da maior componente: " << maxComponentSize << endl;

        cout << "printing Diameter info: " << endl;
        file << "Diameter: " << diameter() << endl;

        cout << "printing components: " << endl;

        for (int i = 0; i < components.size() - 1; i++) {
            file << "Component " << i + 1 << " size: " << components[i].size() << endl;
            for (int j = 0; j < components[i].size(); j++) {
                file << components[i][j] << " ";
            }
            file << '\n' << endl;
        }


    }

    // função que imprime as informações do grafo pedidas pelo trabalho 2
    void printInfo2file_2() {
        string outputFileName = "output_" + inputFile;
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


        cout << "printing dijkstra info: " << endl;
        if (containsNegativeWeight) {
            file << "Graph does contains some negative weight" << endl;
            cout << "Graph does contains some negative weight" << endl;
            return;
        }
        dikjstra(10);
        file << "Dikjstra(10, 20): " << dist[20] << endl;
        file << "Path to 20: ";
        for (int i : getPath(20)) {
            file << i << " ";
        }
        file << endl;
        file << "Dikjstra(10, 30): " << dist[30] << endl;
        file << "Path to 30: ";
        for (int i : getPath(30)) {
            file << i << " ";
        }
        file << endl;
        file << "Dikjstra(10, 40): " << dist[40] << endl;
        file << "Path to 40: ";
        for (int i : getPath(40)) {
            file << i << " ";
        }
        file << endl;
        file << "Dikjstra(10, 50): " << dist[50] << endl;
        file << "Path to 50: ";
        for (int i : getPath(50)) {
            file << i << " ";
        }
        file << endl;
        file << "Dikjstra(10, 60): " << dist[60] << endl;
        file << "Path to 60: ";
        for (int i : getPath(60)) {
            file << i << " ";
        }
        file << endl;

        cout << "time dijkstra info: " << endl;
        file << "time dijkstra info: " << endl;
        file << "Time Dijkstra: " << timeDijkstra() << "s" << endl;

        // cout << "time dijkstraNoHeap info: " << endl;
        // file << "Time DijkstraNoHeap: " << timeDijkstraNoHeap() << "s" << endl;

    }

    // função de debug para testar a entrada
    void debugInput() {
        if (containsNegativeWeight) {
            cout << "Graph does contains some negative weight" << endl;
            return;
        }
        dikjstra(1);
        cout << "Dikjstra(1, 2): " << dist[2] << endl;
        cout << "Path to 2: ";
        for (int i : getPath(2)) {
            cout << i << " ";
        }
        cout << endl;
        cout << "Dikjstra(1, 3): " << dist[3] << endl;
        cout << "Path to 3: ";
        for (int i : getPath(3)) {
            cout << i << " ";
        }
        cout << endl;
        cout << "Dikjstra(1, 4): " << dist[4] << endl;
        cout << "Path to 4: ";
        for (int i : getPath(4)) {
            cout << i << " ";
        }
        cout << endl;
        cout << "Dikjstra(1, 5): " << dist[5] << endl;
        cout << "Path to 5: ";
        for (int i : getPath(5)) {
            cout << i << " ";
        }
        cout << endl;
    }

};