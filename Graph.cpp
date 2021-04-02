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
	char graphType;

	ifstream fileStream(fileName);
	if (!fileStream.is_open()) return;

	fileStream >> graphType;
	fileStream >> this->verticesNum;
	fileStream >> this->isDirected;
	fileStream >> this->isWeighted;
	this->representation = Representation::ADJACENCY_MATRIX;

	vector<int> row;
	int tmp;
	for (int i = 0; i < this->verticesNum; i++) {
		row.clear();
		for (int j = 0; j < this->verticesNum; j++) {
			fileStream >> tmp;
			row.push_back(tmp);
		}
		this->adjMatrix.push_back(row);
	}
}

void Graph::readGraphAdjList(string fileName) {
	char graphType;

	ifstream fileStream(fileName);
	if (!fileStream.is_open()) return;

	fileStream >> graphType;
	fileStream >> this->verticesNum;
	fileStream >> this->isDirected;
	fileStream >> this->isWeighted;
	this->representation = Representation::ADJACENCY_LIST;

	string line;
	getline(fileStream, line);
	int v, w;
	set<tuple<int, int, int>> wSet;
	set<pair<int, int>> uwSet;
	for (int i = 1; i <= this->verticesNum; i++) {
		wSet.clear();
		uwSet.clear();
		getline(fileStream, line);
		istringstream iss(line);
		cout << line << endl;
		while (iss >> v) {
			if (this->isWeighted) {
				iss >> w;
				wSet.insert(make_tuple(i, v, w));
			}
			else {
				uwSet.insert(make_pair(i, v));
			}
		}

		if (this->isWeighted) {
			this->adjListWeighted.push_back(wSet);
		}
		else {
			this->adjList.push_back(uwSet);
		}
	}
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
	ofstream fileStream(fileName);
	if (!fileStream.is_open()) return;

	fileStream << 'C' << ' ' << this->verticesNum << endl;
	fileStream << this->isDirected << ' ' << this->isWeighted << endl;

	bool firstElem;
	for (vector<int> row : this->adjMatrix) {
		firstElem = true;
		for (int elem : row) {
			if (firstElem) {
				firstElem = false;
			}
			else {
				fileStream << " ";
			}
			fileStream << elem;
		}
		fileStream << endl;
	}
}

void Graph::writeGraphAdjList(string fileName) {
	ofstream fileStream(fileName);
	if (!fileStream.is_open()) return;

	fileStream << 'L' << ' ' << this->verticesNum << endl;
	fileStream << this->isDirected << ' ' << this->isWeighted << endl;

	bool firstElem;
	int v1, v2, w;
	if (this->isWeighted) {
		for (set<tuple<int, int, int>> adjVerticesSet : this->adjListWeighted) {
			firstElem = true;
			for (tuple<int, int, int> adjVertices : adjVerticesSet) {
				tie(v1, v2, w) = adjVertices;
				if (firstElem) {
					firstElem = false;
				}
				else {
					fileStream << " ";
				}
				fileStream << v2 << " " << w;
			}
			fileStream << endl;
		}
	}
	else {
		for (set<pair<int, int>> adjVerticesSet : this->adjList) {
			firstElem = true;
			for (pair<int, int> adjVertices : adjVerticesSet) {
				tie(v1, v2) = adjVertices;
				if (firstElem) {
					firstElem = false;
				}
				else {
					fileStream << " ";
				}
				fileStream << v2;
			}
			fileStream << endl;
		}
	}
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
