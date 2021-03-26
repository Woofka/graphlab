#include "Graph.h"


void Graph::readGraph(string fileName) {
	ifstream fileStream(fileName);
	if (!fileStream.is_open()) return;

	char graphType;
	fileStream >> graphType;
	fileStream.close();

	if (graphType == 'C') {
		readGraphAdjMatrix(fileName);
		return;
	}
	if (graphType == 'L') {
		readGraphAdjList(fileName);
		return;
	}
	if (graphType == 'E') {
		readGraphEdgeList(fileName);
		return;
	}
}

void Graph::readGraphAdjMatrix(string fileName) {

}

void Graph::readGraphAdjList(string fileName) {

}

void Graph::readGraphEdgeList(string fileName) {
	char graphType;

	ifstream fileStream(fileName);
	if (!fileStream.is_open()) return;

	fileStream >> graphType;
	fileStream >> this->verticesNum;
	fileStream >> this->edgesNum;
	fileStream >> this->isDirected;
	fileStream >> this->isWeighted;
	this->representation = Representation::EDGE_LIST;

	int v1, v2, weight;
	for (int i = 0; i < this->edgesNum; i++) {
		fileStream >> v1;
		fileStream >> v2;
		if (this->isWeighted) {
			fileStream >> weight;
			this->edgeListWeighted.push_back(make_tuple(v1, v2, weight));
		}
		else {
			this->edgeList.push_back(make_pair(v1, v2));
		}
	}

	fileStream.close();
}

void Graph::addEdge(int from, int to, int weight) {

}

void Graph::removeEdge(int from, int to) {

}

int Graph::changeEdge(int from, int to, int newWeight) {
	// returns old weight value
	return 0;
}

void Graph::transformToAdjList() {

}

void Graph::transformToAdjMatrix() {

}

void Graph::transformToListOfEdges() {

}

void Graph::writeGraph(string fileName) {
	if (this->representation == Representation::ADJACENCY_MATRIX) {
		writeGraphAdjMatrix(fileName);
		return;
	}
	if (this->representation == Representation::ADJACENCY_LIST) {
		writeGraphAdjList(fileName);
		return;
	}
	if (this->representation == Representation::EDGE_LIST) {
		writeGraphEdgeList(fileName);
		return;
	}
}

void Graph::writeGraphAdjMatrix(string fileName) {

}

void Graph::writeGraphAdjList(string fileName) {

}

void Graph::writeGraphEdgeList(string fileName) {
	ofstream fileStream(fileName);
	if (!fileStream.is_open()) return;

	fileStream << 'E' << ' ' << this->verticesNum << ' ' << this->edgesNum << endl;
	fileStream << this->isDirected << ' ' << this->isWeighted << endl;

	int v1, v2, weight;
	if (this->isWeighted) {
		for (auto&& tuple : this->edgeListWeighted) {
			tie(v1, v2, weight) = tuple;
			fileStream << v1 << ' ' << v2 << ' ' << weight << endl;
		}
	}
	else {
		for (auto&& pair : this->edgeList) {
			tie(v1, v2) = pair;
			fileStream << v1 << ' ' << v2 << endl;
		}
	}

	fileStream.close();
}
