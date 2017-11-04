#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Struct representing an edge in the graph.
struct Edge
{
	string u; // Starting city.
	string v; // Ending city.
	int weight; // Distance between the cities.
};

// Struct representing a vertex in the graph.
struct Vertex
{
	string city; // Name of the city in the vertex.
	bool visited; // Whether or not the vertex has already been visited.
	vector<Edge> edgeList; // List of incident edges.
};

// Graph class that uses an adjacency list
class Graph
{
public:
	Graph();
	~Graph();
	bool empty();
	int size();
	void initializeGraph();
	void insertVertex(string city);
	unsigned int findVertex(string city);
	void insertEdge(string u, string v, int weight);
	vector<string> vertices();
	vector<string> edges();

private:
	vector<Vertex> graph;
};

#endif
