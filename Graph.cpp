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
	int distanceTraveled = 0;

	if(allVisited() != graph.size() && allVisited() < 10)
	{
		int currVertex = findVertex(startingCity);

		graph.at(currVertex).visited = true;

		cout << "\nVisited: " << allVisited() << endl << endl;

		int nextVertex = smallestEdge(currVertex, dfs);

		vector<string>::iterator nextCityIt = find(dfs.begin(), dfs.end(), startingCity);

		if(nextCityIt == dfs.end())
		{
			dfs.push_back(startingCity);
		}

//		distanceTraveled += graph.at(currVertex).edgeList.at(nextVertex).weight;

		cout << graph.at(currVertex).city << " was visited, now visiting "
			 << graph.at(nextVertex).city << endl;

		DFS(graph.at(nextVertex).city, dfs);
	}

	return distanceTraveled;
}

int Graph::smallestEdge(int currVertex, vector<string> &dfs)
{
	if(allEdgesVisited(currVertex) != graph.at(currVertex).edgeList.size())
	{
		int smallestEdgeIndex = 0;

		for(unsigned int i = 0; i < graph.at(currVertex).edgeList.size(); i++)
		{
			int smallestVertex = findVertex(graph.at(currVertex).edgeList.at(smallestEdgeIndex).v);
			int compVertex = findVertex(graph.at(currVertex).edgeList.at(i).v);

			cout << "comparing " << graph.at(currVertex).edgeList.at(smallestEdgeIndex).v << " and " << graph.at(currVertex).edgeList.at(i).v << endl;

			if(!(graph.at(smallestVertex).visited))
			{
				if((graph.at(compVertex).visited))
				{
					i++;
				}

				if(graph.at(currVertex).edgeList.at(smallestEdgeIndex).weight >=
				   graph.at(currVertex).edgeList.at(i).weight)
				{
					smallestEdgeIndex = i;

					cout << graph.at(smallestVertex).city << " has not been visited\n";
				}
			}
			else
			{
				if(smallestEdgeIndex + 1 < graph.at(currVertex).edgeList.size())
				{
					smallestEdgeIndex++;
				}
			}
		}

		graph.at(currVertex).edgeList.at(smallestEdgeIndex).discoveryEdge = true;

		string nextCity = graph.at(currVertex).edgeList.at(smallestEdgeIndex).v;

		cout << "The next city is: " << nextCity << endl << endl;

		smallestEdgeIndex = findVertex(nextCity);

		if(graph.at(smallestEdgeIndex).visited)
		{
			cout << graph.at(smallestEdgeIndex).city << " was visited\n\n";
		}

		return smallestEdgeIndex;
	}
	else
	{
		vector<string>::iterator dfsIt = find(dfs.begin(), dfs.end(),
										 	  graph.at(currVertex).city);

		dfsIt--;

		cout << "Backtracking to " << *dfsIt << endl << endl;

		int backIndex = findVertex(*dfsIt);

		return smallestEdge(backIndex, dfs);
	}
}

unsigned int Graph::allVisited()
{
//	cout << "\n\nentering all visited function\n\n";

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

	return numVisited;
}

unsigned int Graph::allEdgesVisited(int currVertex)
{
	int numVisited = 0;

	for(unsigned int i = 0; i < graph.at(currVertex).edgeList.size(); i++)
	{
		if(graph.at(findVertex(graph.at(currVertex).edgeList.at(i).v)).visited)
		{
			numVisited++;
		}
	}

	return numVisited;
}
