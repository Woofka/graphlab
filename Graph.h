#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

class Graph
{
public:
	void readGraph(string fileName);
	void addEdge(int from, int to, int weight);
	void removeEdge(int from, int to);
	int changeEdge(int from, int to, int newWeight);
	void transformToAdjList();
	void transformToAdjMatrix();
	void transformToListOfEdges();
	void writeGraph(string fileName);

private:
	enum class Representation {
		NONE,
		ADJACENCY_MATRIX,
		ADJACENCY_LIST,
		EDGE_LIST
	};
	Representation representation = Representation::NONE;
	int verticesNum;
	int edgesNum;
	bool isDirected;
	bool isWeighted;

	vector<vector<int>> adjMatrix;
	vector<set<pair<int, int>>> adjList;
	vector<set<tuple<int, int, int>>> adjListWeighted;
	vector<pair<int, int>> edgeList;
	vector<tuple<int, int, int>> edgeListWeighted;

	void readGraphAdjMatrix(string fileName);
	void readGraphAdjList(string fileName);
	void readGraphEdgeList(string fileName);
	void writeGraphAdjMatrix(string fileName);
	void writeGraphAdjList(string fileName);
	void writeGraphEdgeList(string fileName);
};
