// file that treats collab network graph


#include <iostream>
#include "graph.cpp"
using namespace std;

void printPath(Graph* g , string researcher, vector<string> &researcher_list, map<string , int> &researcher_map) {
    cout << "Distância para " << researcher << " de índice " << researcher_map[researcher] << ": " << g->getDist(researcher_map[researcher]) << endl;
    cout << "Com caminho:" << endl;
    for (int i : g->getPath(researcher_map[researcher])) {
        cout << i << " ";
    }
    cout << endl;
    for (int i : g->getPath(researcher_map[researcher])) {
        cout << researcher_list[i] << ", ";
    }
    cout << endl;
}

int main(int argc , char const* argv[]) {
    // string inputFile = argv[1];

    map<string , int> researcher_map; // maps name to index
    vector<string> researcher_list; // maps index to name
    string filename = "rede_colaboracao_vertices.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return 0;
    }

    int cnt = 0;
    string line;
    while (!file.eof()) {
        cout << "Reading file: " << cnt++ << " lines read" << '\r';
        getline(file , line);
        if(line.empty()) break;
        int id = stoi(line.substr(0 , line.find(',')));
        string name = line.substr(line.find(',') + 1);
        // cout << id << " " << name << endl;
        researcher_map[name] = id;
        // if (cnt++ == 10) break;
    }
    // cout << "\r\033[K" << "File read! " << edgesCnt << " lines read." << endl;
    cout << "File " << filename << " read! " << cnt << " lines read." << endl;
    researcher_list.resize(researcher_map.size()+1);
    for (auto i : researcher_map) {
        researcher_list[i.second] = i.first;
    }

// graph1->printInfo2file_2();



// Graph* graph1 = new Graph("input.txt");
// graph1->debugInput();

    Graph* graph1 = new Graph("rede_colaboracao.txt");
    cout << "Rodando Dijkstra a partir de Edsger W. Dijkstra com índice " << researcher_map["Edsger W. Dijkstra"] << endl;
    graph1->dikjstra(researcher_map["Edsger W. Dijkstra"]);
    vector<string> researchers_to_check = {
        "Alan M. Turing",
        "J. B. Kruskal",
        "Jon M. Kleinberg",
        "Éva Tardos",
        "Daniel R. Figueiredo"
    };
    for (string researcher : researchers_to_check) {
        printPath(graph1 , researcher , researcher_list , researcher_map);
    }
    delete graph1;
    return 0;
}