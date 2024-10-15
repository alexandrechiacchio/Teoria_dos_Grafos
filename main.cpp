#include <iostream>
#include "graph.cpp"
using namespace std;

int main(int argc, char const *argv[]){
    string inputFile = argv[1];

    Graph* graph1 = new Graph(inputFile);
    graph1->printInfo2file_2();

    // Graph* graph1 = new Graph("input.txt");
    // graph1->debugInput();

    delete graph1;
    return 0;
}