// facebookGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>

//const std::string FACEBOOK_FILENAME = "facebook-links.txt";
const std::string FACEBOOK_FILENAME = "../HW9/facebook-links.txt";
const int DEGREE_CUTOFF = 100;

void addEdge(std::vector<std::unordered_set<int>>& adjList, int u, int v);
int calculateDegree(std::vector<std::unordered_set<int>>& adjList, int node);
double calculateAverageOfAdjacents(std::vector<std::unordered_set<int>>& adjList, int node);

int main()
{
    std::ifstream inFS;
    std::cout << "Opening file " << FACEBOOK_FILENAME << std::endl;
    inFS.open(FACEBOOK_FILENAME);
    if (!inFS.is_open()) {
        std::cout << "Could not open file " << FACEBOOK_FILENAME << std::endl;
        return 1;
    }

    // Read in edge line by line and add edges
    std::vector<std::unordered_set<int>> facebookAdjList;
    std::unordered_map<int, double> averageDegreeOfAdjacents;
    int u, v, lineNum = 0;
    std::string timestamp;
    while (!inFS.eof()) {
    //for (int i = 0; i < 100; i++) {
        lineNum++;
        if (lineNum % 100000 == 0)
            std::cout << "Reading line " << lineNum << std::endl;

        inFS >> u >> v >> timestamp;
        if (!inFS.fail())
            addEdge(facebookAdjList, u, v);
    }
    inFS.close();

    // Compute degree statistics over all vertices
    int numVertices = facebookAdjList.size();
    double meanDegree = 0;
    double frenTotal = 0.0;
    int numDegAtLeastCutoff = 0;
    for (int i = 0; i < facebookAdjList.size(); i++) {
        frenTotal += calculateAverageOfAdjacents(facebookAdjList, i);
        int vertexDeg = facebookAdjList.at(i).size();
        if (vertexDeg >= DEGREE_CUTOFF)
            numDegAtLeastCutoff++;
        if (vertexDeg >= 0)
            meanDegree += vertexDeg / (double) numVertices;
        //std::cout << "Vertex " << i << " has degree " << vertexDeg << std::endl;
    }

    std::cout << "Mean degree: " << meanDegree << std::endl;
    std::cout << "Mean value of mean degree of all a vertex's friends: " << frenTotal / facebookAdjList.size() << std::endl;
    std::cout << "Number of vertices with degree >= " << DEGREE_CUTOFF
        << ": " << numDegAtLeastCutoff << std::endl;

    return 0;
}

void addEdge(std::vector<std::unordered_set<int>>& adjList, int u, int v) {
    // If either node is not already in the outer list, then add it
    if (std::max(u, v) >= adjList.size())
        adjList.resize(std::max(u, v) + 1);

    // Check if v is already in the inner set for node u, and if not, add it,
    // and vice versa
    if (adjList.at(u).count(v) == 0)
        adjList.at(u).insert(v);
    if (adjList.at(v).count(u) == 0)
        adjList.at(v).insert(u);
}

int calculateDegree(std::vector<std::unordered_set<int>>& adjList, int node) {
    return adjList.at(node).size();
}

double calculateAverageOfAdjacents(std::vector<std::unordered_set<int>>& adjList, int node) {
    if (calculateDegree(adjList, node) <= 0) {
        return 0.0;
    }
    int sum = 0;
    for (auto i: adjList.at(node)) {
        sum += calculateDegree(adjList, i);
    }

    return ((double)(sum) / (double)(calculateDegree(adjList, node)));
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

