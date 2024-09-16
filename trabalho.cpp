#include <iostream>
#include <vector>
using namespace std;

class Node {
  vector<Node*> adj;
  int data;
public:
  Node(int data) {
    this->data = data;
  }

  void addAdj(Node* node) {
    adj.push_back(node);
  }

  vector<Node*> getAdj() {
    return adj;
  }

  int getData() {
    return data;
  }
};



class Graph {

  vector<Node> nodes;

public:
  Graph() {}
  void addNode(int data) {
    Node node(data);
    nodes.push_back(node);
  }

  void addEdge(int data1, int data2) {
    Node* node1 = nullptr;
    Node* node2 = nullptr;

    for (Node& node : nodes) {
      if (node.getData() == data1) {
        node1 = &node;
      }
      if (node.getData() == data2) {
        node2 = &node;
      }
    }

    if (node1 == nullptr || node2 == nullptr) {
      cout << "Node not found" << endl;
      return;
    }

    node1->addAdj(node2);
    node2->addAdj(node1);
  }

  void print() {
    for (Node& node : nodes) {
      cout << node.getData() << ": ";
      for (Node* adj : node.getAdj()) {
        cout << adj->getData() << " ";
      }
      cout << endl;
    }
  }

  int size() {
    return nodes.size();
  }

  int EdgeSize() {
    int count = 0;
    for (Node& node : nodes) {
      count += node.getAdj().size();
    }
    return count / 2;
  }

  int degree(int data) {
    for (Node& node : nodes) {
      if (node.getData() == data) {
        return node.getAdj().size();
      }
    }
    return -1;
  }

  int maxDegree() {
    int max = 0;
    for (Node& node : nodes) {
      int degree = node.getAdj().size();
      if (degree > max) {
        max = degree;
      }
    }
    return max;
  }

  int minDegree() {
    int min = 0;
    for (Node& node : nodes) {
      int degree = node.getAdj().size();
      if (degree < min) {
        min = degree;
      }
    }
    return min;
  }

  double avgDegree() {
    return 2 * EdgeSize() / size();
  }

  int medianDegree() {
    vector<int> degrees;
    for (Node& node : nodes) {
      degrees.push_back(node.getAdj().size());
    }
    sort(degrees.begin(), degrees.end());
    return degrees[degrees.size() / 2];
  }

  void printInfo(){
    cout << "Number of nodes: " << size() << endl;
    cout << "Number of edges: " << EdgeSize() << endl;
    cout << "Max degree: " << maxDegree() << endl;
    cout << "Min degree: " << minDegree() << endl;
    cout << "Avg degree: " << avgDegree() << endl;
    cout << "Median degree: " << medianDegree() << endl;
  }

  Graph DFS(Node node, Graph graph) {
    vector<Node*> visited;
    vector<Node*> stack;
    stack.push_back(&node);
    while (!stack.empty()) {
      Node* current = stack.back();
      stack.pop_back();
      if (find(visited.begin(), visited.end(), current) == visited.end()) {
        visited.push_back(current);
        for (Node* adj : current->getAdj()) {
          stack.push_back(adj);
          graph.addEdge(current->getData(), adj->getData());
        }
      }
    }
    return graph;

    Graph BFS(Node node, Graph graph) {
      vector<Node*> visited;
      vector<Node*> queue;
      queue.push_back(&node);
      while (!queue.empty()) {
        Node* current = queue.front();
        queue.erase(queue.begin());
        if (find(visited.begin(), visited.end(), current) == visited.end()) {
          visited.push_back(current);
          for (Node* adj : current->getAdj()) {
            queue.push_back(adj);
            graph.addEdge(current->getData(), adj->getData());
          }
        }
      }
      return graph;
    }
  }

};


int main() {
  Graph graph;
  graph.addNode(1);
  graph.addNode(2);
  graph.addNode(3);
  graph.addNode(4);
  graph.addNode(5);
  graph.addEdge(1, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 4);
  graph.addEdge(3, 5);
  graph.print();
  return 0;
}