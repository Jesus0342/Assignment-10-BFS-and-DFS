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

int Graph::DFS(string startingCity, vector<string> &dfs)
{
	cout << "\n\nentering dfs function";

	int distanceTraveled = 0;

	if(allVisited() != graph.size())
	{
		cout << "\n\ndfs if statement\n\n";

		int currentVertex = findVertex(startingCity);

		graph.at(currentVertex).visited = true;

		int nextVertex = smallestEdge(currentVertex, dfs);
//
//		dfs.push_back(startingCity);
//
//		distanceTraveled += graph.at(currentVertex).edgeList.at(nextVertex).weight;
//
//		cout << graph.at(currentVertex).city << " was visited, now visiting " <<
//				graph.at(nextVertex).city << endl;

//		return distanceTraveled +
//			   DFS(graph.at(currentVertex).edgeList.at(nextVertex).v, dfs);
	}
}

int Graph::smallestEdge(int currentVertex, vector<string> &dfs)
{
	cout << "\n\nentering smallest edge function\n\n";

	if(allEdgesVisited(currentVertex) != graph.at(currentVertex).edgeList.size())
	{
		int smallestEdgeIndex = 0;
		int compIndex = 0;
//
//		for(unsigned int i = 0; i < graph.at(currentVertex).edgeList.size(); i++)
//		{
//			if(graph.at(currentVertex).edgeList.at(smallestEdgeIndex).weight >
//			   graph.at(currentVertex).edgeList.at(compIndex).weight)
//			{
//				if(graph.at(findVertex(graph.at(currentVertex).edgeList.at(compIndex).v)).visited == false)
//				{
//					smallestEdgeIndex = compIndex;
//				}
//			}
//
//			compIndex++;
//		}
//
//		graph.at(currentVertex).edgeList.at(smallestEdgeIndex).discoveryEdge = true;
//		graph.at(currentVertex).edgeList.at(smallestEdgeIndex).backEdge = false;
//
//		return smallestEdgeIndex;
	}
//	else
//	{
//		int backIndex = findVertex(dfs.back());
//
//		return smallestEdge(backIndex, dfs);
//	}
}

unsigned int Graph::allVisited()
{
	cout << "\n\nentering all visited function\n\n";

	int numVisited = 0;

	vector<Vertex>::iterator graphIt = graph.begin();

	while(graphIt != graph.end())
	{
		if(graphIt->visited)
		{
			numVisited++;
		}

		graphIt++;
	}

	cout << "Entering all visited function...\n\n" << numVisited << " vertices visted.\n\n";

	return numVisited;
}

unsigned int Graph::allEdgesVisited(int currentVertex)
{
	cout << "\n\nentering all edges visited function\n\n";

	int numVisited = 0;

	for(unsigned int i = 0; i < graph.at(currentVertex).edgeList.size(); i++)
	{
		cout << graph.at(currentVertex).edgeList.at(i).v << endl;
	}

	return numVisited;
}
