#include <iostream>
#include <fstream>
#include <string>

#include <forward_list>
#include <unordered_map>
#include <unordered_set>

#define FILE_PATH "facebook-links.txt"

#define FILE_ERROR 1

using namespace std;

class UndirectedGraph {
    public:
        void addEdge(int vertex1, int vertex2);
        void printEdges(int vertex);

        double getAverageDegree();
        int countLargeDegrees();
        ~UndirectedGraph();
    private:
        unordered_map<int, unordered_set<int>*> edgeList;
};

UndirectedGraph::~UndirectedGraph() {
    for (auto i: edgeList) {
        delete i.second;
    }
}

void UndirectedGraph::addEdge(int vertex1, int vertex2) {
    if (!edgeList.count(vertex1)) {
        edgeList.emplace(vertex1, new unordered_set<int>());
    }

    if (!edgeList.count(vertex2)) {
        edgeList.emplace(vertex2, new unordered_set<int>());
    }

    edgeList.at(vertex1)->emplace(vertex2);
    edgeList.at(vertex2)->emplace(vertex1);
}

void UndirectedGraph::printEdges(int vertex) {
    auto vertexEdges = edgeList.at(vertex);

    cout << "Edges for vertex " << vertex << ": ";

    for (auto itr = vertexEdges->begin(); itr != vertexEdges->end(); ++itr) {
        cout << *itr << " ";
    }
}

double UndirectedGraph::getAverageDegree() {
    int sum = 0;

    for (auto i: edgeList) {
        sum += i.second->size();
    }

    return (double)(sum) / (double)(edgeList.size());
}

int UndirectedGraph::countLargeDegrees() {
    int cnt = 0;

    for (auto i: edgeList) {
        if (i.second->size() >= 100) {
            cnt++;
        }
    }

    return cnt;
}

int main() {
    ifstream facebookFS;
    facebookFS.open(FILE_PATH);

    if (!facebookFS.is_open()) {
        cout << "Error opening file.";
        exit(FILE_ERROR);
    }

    string currentLine;
    int breakCount = 0;
    UndirectedGraph g;

    while (getline(facebookFS, currentLine)) {
        int firstTab = currentLine.find('\t');
        int user = stoi(currentLine.substr(0, firstTab));
        int userFriend = stoi(currentLine.substr(firstTab + 1, currentLine.find('\t', firstTab + 1)));

        g.addEdge(user, userFriend);

        if (breakCount > 100) {
            break;
        }
    }
    
    cout << "Average degree: " << g.getAverageDegree() << endl;
    cout << "Number of vertices with degree >= 100: " << g.countLargeDegrees() << endl;

    return 0;
}