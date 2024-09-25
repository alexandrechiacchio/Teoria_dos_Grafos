#include <iostream>
#include "graph.cpp"
using namespace std;

int main(){
    string inputFile = "grafo_2.txt";
    Graph* graph1 = new Graph(vector_t , inputFile);
    graph1->printInfo2file();
    delete graph1;

    Graph* graph2 = new Graph(list_t , inputFile);
    graph2->printInfo2file();
    delete graph2;

    Graph* graph3 = new Graph(matrix_t , inputFile);
    graph3->printInfo2file();
    delete graph3;
}