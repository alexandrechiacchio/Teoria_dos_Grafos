#include <vector>
#include <list>
#include <algorithm>
#include <cstring> //memset
using namespace std;

typedef enum {
  vector_t ,
  list_t ,
  matrix_t
} Adjecencytype;


class AbstractAdj {
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
  int edgeCnt = 0;
public:

  MatrixAdj(int _size) {
    size = _size + 1;
    cout << "asdasd\n";
    matrixAdj = new int[size * size];
    cout << "asdasd\n";
    memset(matrixAdj , 0 , size * size * sizeof(int));
  }

  void addEdge(int u , int v) {
    if(matrixAdj[u * size + v] == true) return;
    matrixAdj[u * size + v] = true;
    matrixAdj[v * size + u] = true;
    edgeCnt++;
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
    return edgeCnt;
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
    return adj;
  }

};

class ListAdj : public AbstractAdj {
  list<int>* listAdj;
  int size;
  int edgeCnt = 0;
public:

  ListAdj(int _size) {
    size = _size + 1;
    listAdj = new list<int>[size];
  }

  void addEdge(int u , int v) {
    if(find(listAdj[u].begin() , listAdj[u].end() , v) != listAdj[u].end()) return;
    listAdj[u].push_back(v);
    listAdj[v].push_back(u);
    edgeCnt++;
  }

  int degree(int u) {
    return listAdj[u].size();
  }

  int EdgeSize() {
    return edgeCnt;
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
  int edgeCnt = 0;
public:

  VectorAdj(int _size) {
    size = _size + 1;
    vectorAdj = new vector<int>[size];
  }

  void addEdge(int u , int v) {
    if(find(vectorAdj[u].begin(), vectorAdj[u].end(), v) != vectorAdj[u].end()) return;
    vectorAdj[u].push_back(v);
    vectorAdj[v].push_back(u);
    edgeCnt++;
  }

  int degree(int u) {
    return vectorAdj[u].size();
  }

  int EdgeSize() {
    return edgeCnt;
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