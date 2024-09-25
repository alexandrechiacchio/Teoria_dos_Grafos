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
public:

  MatrixAdj(int _size) {
    size = _size + 1;
    matrixAdj = new int[size * size];
    memset(matrixAdj , 0 , size * size * sizeof(int));
  }

  void addEdge(int u , int v) {
    matrixAdj[u * size + v] = 1;
    matrixAdj[v * size + u] = 1;
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
    int count = 0;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        if (matrixAdj[i * size + j] == 1) {
          count++;
        }
      }
    }
    return count / 2;
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
    int min = 0;
    for (int i = 0; i < size; i++) {
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
    int min = 0;
    for (int i = 0; i < size; i++) {
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
    int min = 0;
    for (int i = 0; i < size; i++) {
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
    return vectorAdj[u];
  }

};

class Node {
  int depth = 0;
  int parent = 0;
  bool visited = false;
public:

  Node() {}

  void reset() {
    depth = 0;
    parent = 0;
    visited = false;
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

};



class Graph {
  vector<Node*> nodes;
  AbstractAdj* adj;
  int edgeCnt = 0;
  string inputFile;
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

  void readInput(string filename) {

    ifstream file(filename);
    if (!file.is_open()) {
      std::cerr << "Error opening file: " << filename << std::endl;
      return;
    }

    int n;
    file >> n;

    nodes.resize(n + 1 , new Node());
    for (int i = 0; i < n; i++) {
      nodes[i]->setParent(i);
    }

    while (!file.eof()) {
      edgeCnt++;
      int a , b;
      file >> a >> b;
      adj->addEdge(a , b);
    }
  }


  void addNode(int data) {
    Node* newNode = new Node();
    nodes.push_back(newNode);
  }

  void addEdge(int u , int v) {
    adj->addEdge(u , v);
    adj->addEdge(v , u);
  }

  // void print() {
  //   for (Node* node : nodes) {
  //     cout << node->getData() << ": ";
  //     for (Node* adj : node->getAdj()) {
  //       cout << adj->getData() << " ";
  //     }
  //     cout << endl;
  //   }
  // }

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



  int DFS(int u) {
    vector<int> depth(size() + 1 , 0);
    for (int i = 0; i <= size(); i++) {
      nodes[i]->reset();
      nodes[i]->setParent(i);
    }
    vector<bool> visited(size() + 1 , false);
    vector<int> parent(size() + 1 , 0);
    stack<int> stack_graph;
    stack_graph.push(u);
    parent[u] = u;
    while (!(stack_graph.empty())) {
      int v = stack_graph.top(); stack_graph.pop();
      if (visited[v] == false) {
        visited[v] = true;
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
    vector<bool> visited(size() + 1 , false);
    for (int i = 0; i <= size(); i++) {
      nodes[i]->reset();
      nodes[i]->setParent(i);
    }
    queue<int> queue_graph;
    queue_graph.push(u);
    visited[u] = true;
    while (!(queue_graph.empty())) {
      int v = queue_graph.front(); queue_graph.pop();
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
    clock_t start = clock();
    srand(clock());
    for (int i = 0; i < 100; i++)
      DFS(((rand() % size()) + 1) % size());
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
  }

  // average time in seconds to run BFS 100 times
  double timeBFS() {
    clock_t start = clock();
    srand(clock());
    for (int i = 0; i < 100; i++)
      BFS(((rand() % size()) + 1) % size());
    clock_t end = clock();
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
    ofstream file("output_" + inputFile);
    if (!file.is_open()) {
      std::cerr << "Error opening file: " << "output.txt" << std::endl;
      return;
    }

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
    file << "Time DFS: " << timeDFS() << "s" << endl;
    file << "Time BFS: " << timeBFS() << "s" << endl;

    for (int i = 1; i <= 3; i++) {
      file << "DFS(" << i << ")" << endl;
      DFS(i);
      file << "parent[1] = " << nodes[1]->getParent() << endl;
      file << "parent[2] = " << nodes[2]->getParent() << endl;
      file << "parent[3] = " << nodes[3]->getParent() << endl;
    }

    for (int i = 1; i <= 3; i++) {
      file << "BFS(" << i << ")" << endl;
      BFS(i);
      file << "parent[1] = " << nodes[1]->getParent() << endl;
      file << "parent[2] = " << nodes[2]->getParent() << endl;
      file << "parent[3] = " << nodes[3]->getParent() << endl;
    }

    BFS(10);
    file << "Distance between 10 and 20: " << nodes[20]->getDepth() << endl;
    file << "Distance between 10 and 30: " << nodes[30]->getDepth() << endl;
    BFS(20);
    file << "Distance between 20 and 30: " << nodes[30]->getDepth() << endl;

    int connectedComponets = 0;
    int maxComponentSize = -1;
    int minComponentSize = size() + 1;
    for (int i = 1; i <= size(); i++) {
      if (nodes[i]->isVisited() == false) {
        connectedComponets++;
        int componentSize = BFS(i);
        if (componentSize > maxComponentSize) maxComponentSize = componentSize;
        if (componentSize < minComponentSize) minComponentSize = componentSize;
      }
    }
    file << "Number of connected components: " << connectedComponets << endl;
    file << "Max component size: " << maxComponentSize << endl;
    file << "Min component size: " << minComponentSize << endl;

    file << "Diameter: " << diameter() << endl;

    // BFS(1);
    // cout << "BFS(1)" << endl;

    // for(int i = 0; i <= size(); i++){
    //   cout << "Node " << i << " depth: " << nodes[i]->getDepth() << " parent: " << nodes[i]->getParent() << endl;
    // }
  }
};


int main() {
  Graph* graph = new Graph(vector_t , "grafo_1.txt");

  graph->printInfo2file();
  return 0;
}
