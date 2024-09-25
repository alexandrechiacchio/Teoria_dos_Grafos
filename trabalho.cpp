#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <sys/resource.h>
#include <climits>
#include <set>
#include <iomanip>
using namespace std;

typedef enum {
  vector_t ,
  list_t ,
  matrix_t
} Adjecencytype;


class AbstractAdj {
  // vector<int>* vectorAdj;
  // list<int>* listAdj;
  // int* matrixAdj;
  int size;
  Adjecencytype type;
public:

  virtual ~AbstractAdj() {}

  virtual void addEdge(int , int) = 0;
  virtual int degree(int) = 0;
  virtual int EdgeSize() = 0;
  virtual int maxDegree() = 0;
  virtual int minDegree() = 0;
  virtual double avgDegree() = 0;
  virtual int medianDegree() = 0;
  virtual vector<int> getAdj(int u) = 0;

};

class MatrixAdj : public AbstractAdj {
  int* matrixAdj;
  int size;
  int edgesizei = 0;
public:

  MatrixAdj(int _size) {
    size = _size + 1;
    matrixAdj = new int[size * size];
    memset(matrixAdj , 0 , size * size * sizeof(int));
  }

  void addEdge(int u , int v) {
    if(matrixAdj[u * size + v] == true) return;
    matrixAdj[u * size + v] = true;
    matrixAdj[v * size + u] = true;
    edgesizei++;
  }


  int degree(int u) {
    int count = 0;
    for (int i = 0; i < size; i++) {
      if (matrixAdj[u * size + i] == 1) {
        count++;
      }
    }
    return count;
  }

  int EdgeSize() {
    return edgesizei;
  }

  int maxDegree() {
    int max = 0;
    for (int i = 0; i < size; i++) {
      int degree = 0;
      for (int j = 0; j < size; j++) {
        if (matrixAdj[i * size + j] == 1) {
          degree++;
        }
      }
      if (degree > max) {
        max = degree;
      }
    }
    return max;
  }

  int minDegree() {
    int min = size+1;
    for (int i = 1; i < size; i++) {
      int degree = 0;
      for (int j = 0; j < size; j++) {
        if (matrixAdj[i * size + j] == 1) {
          degree++;
        }
      }
      if (degree < min) {
        min = degree;
      }
    }
    return min;
  }

  double avgDegree() {
    return (double)2 * EdgeSize() / size;
  }

  int medianDegree() {
    vector<int> degrees;
    for (int i = 0; i < size; i++) {
      int degree = 0;
      for (int j = 0; j < size; j++) {
        if (matrixAdj[i * size + j] == 1) {
          degree++;
        }
      }
      degrees.push_back(degree);
    }
    sort(degrees.begin() , degrees.end());
    return degrees[degrees.size() / 2];
  }

  vector<int> getAdj(int u) {
    vector<int> adj;
    for (int i = 0; i < size; i++) {
      if (matrixAdj[u * size + i] == 1) {
        adj.push_back(i);
      }
    }
    sort(adj.begin() , adj.end());
    return adj;
  }

};

class ListAdj : public AbstractAdj {
  list<int>* listAdj;
  int size;
public:

  ListAdj(int _size) {
    size = _size + 1;
    listAdj = new list<int>[size];
  }

  void addEdge(int u , int v) {
    if(find(listAdj[u].begin() , listAdj[u].end() , v) != listAdj[u].end()) return;
    listAdj[u].push_back(v);
    listAdj[v].push_back(u);
  }

  int degree(int u) {
    return listAdj[u].size();
  }

  int EdgeSize() {
    int count = 0;
    for (int i = 0; i < size; i++) {
      count += listAdj[i].size();
    }
    return count / 2;
  }

  int maxDegree() {
    int max = 0;
    for (int i = 0; i < size; i++) {
      int degree = listAdj[i].size();
      if (degree > max) {
        max = degree;
      }
    }
    return max;
  }

  int minDegree() {
    int min = size+1;
    for (int i = 1; i < size; i++) {
      int degree = listAdj[i].size();
      if (degree < min) {
        min = degree;
      }
    }
    return min;
  }

  double avgDegree() {
    return (double)2 * EdgeSize() / size;
  }

  int medianDegree() {
    vector<int> degrees;
    for (int i = 0; i < size; i++) {
      degrees.push_back(listAdj[i].size());
    }
    sort(degrees.begin() , degrees.end());
    return degrees[degrees.size() / 2];
  }

  vector<int> getAdj(int u) {
    vector<int> adj;
    for (int i : listAdj[u]) {
      adj.push_back(i);
    }
    sort(adj.begin() , adj.end());
    return adj;
  }

};

class VectorAdj : public AbstractAdj {
  vector<int>* vectorAdj;
  int size;
public:

  VectorAdj(int _size) {
    size = _size + 1;
    vectorAdj = new vector<int>[size];
  }

  void addEdge(int u , int v) {
    if(find(vectorAdj[u].begin(), vectorAdj[u].end(), v) != vectorAdj[u].end()) return;
    vectorAdj[u].push_back(v);
    vectorAdj[v].push_back(u);
  }

  int degree(int u) {
    return vectorAdj[u].size();
  }

  int EdgeSize() {
    int count = 0;
    for (int i = 0; i < size; i++) {
      count += vectorAdj[i].size();
    }
    return count / 2;
  }

  int maxDegree() {
    int max = 0;
    for (int i = 0; i < size; i++) {
      int degree = vectorAdj[i].size();
      if (degree > max) {
        max = degree;
      }
    }
    return max;
  }

  int minDegree() {
    int min = size+1;
    for (int i = 1; i < size; i++) {
      int degree = vectorAdj[i].size();
      if (degree < min) {
        min = degree;
      }
    }
    return min;
  }

  double avgDegree() {
    return (double)2 * EdgeSize() / size;
  }

  int medianDegree() {
    vector<int> degrees;
    for (int i = 0; i < size; i++) {
      degrees.push_back(vectorAdj[i].size());
    }
    sort(degrees.begin() , degrees.end());
    return degrees[degrees.size() / 2];
  }

  vector<int> getAdj(int u) {
    sort(vectorAdj[u].begin() , vectorAdj[u].end());
    return vectorAdj[u];
  }

};

class Node {
  int depth = 0;
  int parent = 0;
  bool visited = false;
  int component = 0;
public:

  Node() {}

  void reset() {
    depth = 0;
    parent = 0;
    visited = false;
    int component = 0;
  }

  void setParent(int _parent) {
    parent = _parent;
  }

  int getParent() {
    return parent;
  }

  void setDepth(int _depth) {
    depth = _depth;
  }

  int getDepth() {
    return depth;
  }

  bool isVisited() {
    return visited;
  }

  void visit() {
    visited = true;
  }

  void setComponent(int _component) {
    component = _component;
  }

  int getComponent() {
    return component;
  }

};



class Graph {
  vector<Node*> nodes;
  AbstractAdj* adj;
  int edgeCnt = 0;
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

    int size;
    file >> size;

    if (type == vector_t) {
      adj = new VectorAdj(size);
    } else if (type == list_t) {
      adj = new ListAdj(size);
    } else {
      adj = new MatrixAdj(size);
    }

    nodes.resize(size + 1 , new Node());
    for (int i = 0; i <= size; i++) {
      nodes[i] = new Node();
    }
    // cout << nodes[0] == nodes[1] << endl;

    while (!file.eof()) {
      edgeCnt++;
      int a , b;
      file >> a >> b;
      adj->addEdge(a , b);
    }

  }



  int size() {
    return nodes.size() - 1;
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

  void reset(){
    componentCnt = 0;
    for(int i = 0; i <= size(); i++){
      nodes[i]->reset();
      nodes[i]->setParent(i);
    }
  }


  int DFS(int u) {
    componentCnt++;
    vector<int> depth(size() + 1 , 0);
    vector<bool> visited(size() + 1 , false);
    vector<int> parent(size() + 1 , 0);
    stack<int> stack_graph;
    stack_graph.push(u);
    nodes[u]->setComponent(componentCnt);
    parent[u] = u;
    while (!(stack_graph.empty())) {
      int v = stack_graph.top(); stack_graph.pop();
      if (visited[v] == false) {
        visited[v] = true;
        nodes[v]->setComponent(componentCnt);
        nodes[v]->visit();
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
    clock_t start, end;
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
    clock_t start, end;
    for (int i = 0; i < 100; i++)
      reset();
      start = clock();
      BFS(((rand() % size()) + 1) % size());
      end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
  }

  vector<vector<int>> FloydWarshall(){
    cout << "Running Floyd Warshall\r";
    vector<vector<int>> dist(size() + 1, vector<int>(size() + 1, size()+10));
    for(int i = 1; i<=size(); i++){
      vector<int> aux = adj->getAdj(i);
      for(int j = 0; j<aux.size(); j++){
        dist[i][aux[j]] = 1;
      }
    }
    for(int i = 0; i<=size(); i++){
      dist[i][i] = 0;
    }
    for(int k = 1; k<=size(); k++){
      for(int i = 1; i<=size(); i++){
        for(int j = 1; j<=size(); j++){
          if(i != j && i != k && j != k){
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }
    return dist;
  }

  int diameter(int tol = 1e4){
    cout << "Finding Diameter\r\n";
    int diameter = -1;
    reset();
    for(int i = 1; i<=size() && i <= tol; i++){
      BFS(i);
      for(int i = 1; i<=size(); i++){
        if(nodes[i]->getDepth() > diameter){
          diameter = nodes[i]->getDepth();
        }
      }
    }
    return diameter;
  }

  void printInfo() {
    cout << "Number of nodes: " << size() << endl;
    cout << "Number of edges: " << EdgeSize() << endl;
    cout << "Max degree: " << maxDegree() << endl;
    cout << "Min degree: " << minDegree() << endl;
    cout << "Avg degree: " << avgDegree() << endl;
    cout << "Median degree: " << medianDegree() << endl;
  }

  void printInfo2file() {
    int counter = 0;
    string outputFileName = "output_(0)" + inputFile;
    ifstream testFile(outputFileName);
    while (testFile.good()) {
      counter++;
      outputFileName = "output(" + to_string(counter) + ")_" + inputFile;
      testFile.close();
      testFile.open(outputFileName);
    }
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
      file << "parent[10] = " << nodes[10]->getParent() << endl;
      file << "parent[20] = " << nodes[20]->getParent() << endl;
      file << "parent[30] = " << nodes[30]->getParent() << endl;
    }

    for (int i = 1; i <= 3; i++) {
      file << "BFS(" << i << ")" << endl;
      reset();
      BFS(i);
      file << "parent[10] = " << nodes[10]->getParent() << endl;
      file << "parent[20] = " << nodes[20]->getParent() << endl;
      file << "parent[30] = " << nodes[30]->getParent() << endl;
    }

    reset();
    BFS(10);
    file << "Distance between 10 and 20: " << nodes[20]->getDepth() << endl;
    file << "Distance between 10 and 30: " << nodes[30]->getDepth() << endl;
    reset();
    BFS(20);
    file << "Distance between 20 and 30: " << nodes[30]->getDepth() << endl;

    cout << "printing connected components info: " << endl;
    int connectedComponets = 0;
    int maxComponentSize = -1;
    int minComponentSize = size() + 1;
    reset();
    for (int i = 1; i <= size(); i++) {
      if (nodes[i]->isVisited() == false) {
        BFS(i);
      }
    }

    for(Node* node : nodes){
      connectedComponets = max(connectedComponets, node->getComponent());
    }

    // cout << connectedComponets << endl;

    vector<vector<int>> components(connectedComponets+1);

    for(int i = 1; i<=size(); i++){
      components[nodes[i]->getComponent()].push_back(i);
    }

    sort(components.begin(), components.end(), [](vector<int> a, vector<int> b){
      return a.size() > b.size();
    });

    for(int i = 0; i<connectedComponets; i++){
      maxComponentSize = max(maxComponentSize, (int)components[i].size());
      minComponentSize = min(minComponentSize, (int)components[i].size());
    }

    file << "Number of connected components: " << connectedComponets << endl;
    file << "Max component size: " << maxComponentSize << endl;
    file << "Min component size: " << minComponentSize << endl;

    for(int i = 0; i<connectedComponets; i++){
      file << "Component " << i+1 << " size: " << components[i].size() << endl;
      for(int j = 0; j<components[i].size(); j++){
        file << components[i][j] << " ";
        if(j+1 != components[i][j]) cout << "Error" << endl;
      }
    }

    sort(components.begin(), components.end(), [](vector<int> a, vector<int> b){
      return a.size() > b.size();
    });

    for(int i = 0; i<components.size(); i++){
      file << "Component " << i+1 << " size: " << components[i].size() << endl;
      for(int j = 0; j<components[i].size(); j++){
        file << components[i][j] << " ";
        if(j+1 != components[i][j]) cout << "Error" << endl;
      }
    }
    file << endl;

    cout << "printing Diameter info: " << endl;
    file << "Diameter: " << diameter() << endl;

    // BFS(1);
    // cout << "BFS(1)" << endl;

    // for(int i = 0; i <= size(); i++){
    //   cout << "Node " << i << " depth: " << nodes[i]->getDepth() << " parent: " << nodes[i]->getParent() << endl;
    // }
  }
};


int main(int argc , char* argv[]) {
  Adjecencytype type = (Adjecencytype)atoi(argv[1]); // 0 = vector, 1 = list, 2 = matrix
  Graph* graph = new Graph(type , "grafo_1.txt");

  graph->printInfo2file();


  // Graph* graph1 = new Graph(matrix_t , "grafo_1.txt");
  // Graph* graph2 = new Graph(vector_t , "grafo_1.txt");

  // for (int i = 0; i < 10000; i++) {
  //   vector<int> aux1 = graph1->adj->getAdj(i);
  //   vector<int> aux2 = graph2->adj->getAdj(i);
  //   bool flag = true;
  //   for(int j = 0; j < aux1.size(); j++){
  //     if(aux1[j] != aux2[j]){
  //       flag = false;
  //       for (int k = 0; k < aux1.size(); k++) {
  //         cout << aux1[k] << " ";
  //       }
  //       cout << endl;
  //       for (int k = 0; k < aux2.size(); k++) {
  //         cout << aux2[k] << " ";
  //       }
  //       break;
  //     }
  //   }
  //   if (flag == false) {
  //     cout << "Error" << endl;
  //     break;
  //   }
  // }

  // ifstream file("grafo_1.txt");
  // int aux1, aux2;
  // file >> aux1;
  // set<pair<int, int>> v;
  // int cnt = 0;
  // while (!file.eof()) {
  //   file >> aux1 >> aux2;
  //   if(aux1>aux2) swap(aux1, aux2);
  //   if(v.count({aux1, aux2})){
  //     cout << aux1 << " " << aux2 << " already in graph" << endl;
  //     cnt++;
  //   }
  //   v.insert({aux1, aux2});
  // }
  // cout << cnt << " repeated edges" << endl;
  return 0;
}
