#include "Graph.h"

Graph::Graph()
{

}

Graph::~Graph()
{

}

bool Graph::empty()
{
	return graph.empty();
}

int Graph::size()
{
	return graph.size();
}

void Graph::initializeGraph()
{
	fstream fin; // File stream variable.

	// Opens the file.
	fin.open("Map.txt");

	// Reads in the contents of the file.
	while(!fin.eof())
	{
		string u; // Starting city.
		string v; // Ending city.
		int weight; // Distance between the cities.

		getline(fin, u, ',');
		getline(fin, v, ',');
		fin >> weight;
		fin.ignore(1000, '\n');

		// Inserts the edge to the graph.
		insertEdge(u, v, weight);
	}

	fin.close();
}

unsigned int Graph::findVertex(string city)
{
	unsigned int index = 0;
	bool found = false;

	// Searches for the city in the graph and returns the index of the graph it
	// was found, else returns the size of the graph.
	while(index < graph.size() && !found)
	{
		if(graph.at(index).city == city)
		{
			found = true;
		}
		else
		{
			index++;
		}
	}

	return index;
}
void Graph::insertVertex(string city)
{
	// Adds the vertex to the graph if it does not yet exist.
	if(findVertex(city) == graph.size())
	{
		Vertex newVertex;

		newVertex.city = city;
		newVertex.visited = false;

		graph.push_back(newVertex);
	}
}

void Graph::insertEdge(string u, string v, int weight)
{
	// Returns the index of the vertex.
	unsigned int index = findVertex(u);

	// Adds the vertex to the graph if it does not yet exist and performs a
	// recursive call, else adds the edge to the edgeList of the specified vertex.
	if(index == graph.size())
	{
		insertVertex(u);

		insertEdge(u, v, weight);
	}
	else
	{
		Edge newEdge;

		newEdge.u = u;
		newEdge.v = v;
		newEdge.weight = weight;

		graph.at(index).edgeList.push_back(newEdge);
	}
}

vector<string> Graph::vertices()
{
	vector<string> cityNames;

	for(unsigned int i = 0; i < graph.size(); i++)
	{
		cityNames.push_back(graph[i].city);
	}

	return cityNames;
}

vector<string> Graph::edges()
{
	vector<string> edgeList;

	for(unsigned int i = 0; i < graph.size(); i++)
	{
		if(graph.at(i).edgeList.size() != 0)
		{
			for(unsigned int j = 0; j < graph.at(i).edgeList.size(); j++)
			{
				edgeList.push_back("(" + graph.at(i).edgeList.at(j).u + ", "
									   + graph.at(i).edgeList.at(j).v + ")");
			}
		}
	}

	return edgeList;
}
