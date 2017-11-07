/******************************************************************************
 * AUTHORS        : Jesus Sanchez & Jason Zhang
 * ASSIGNMENT #10 : BFS & DFS
 * CLASS          : CS1D
 * SECTION        : MW: 3:00pm
 * DUE DATE       : 11/08/2017
 *****************************************************************************/

#include "Graph.h"

/******************************************************************************
 * DFS & BFS
 * ----------------------------------------------------------------------------
 * <Program Description>
 * ----------------------------------------------------------------------------
 * INPUT:
 *
 *
 * OUTPUT:
 *
 *
 *****************************************************************************/
int main()
{
	Graph graph;

	// Initializes the graph by reading from Map.txt.
	graph.initializeGraph();

	// Prints the size of the graph.
	cout << graph.size() << endl << endl;

	// Returns a list of the cities and edges of the graph.
	vector<string> cities = graph.vertices();
	vector<string> edgeList = graph.edges();
	vector<string> dfs;

	// Prints a list of the cities.
	for(unsigned int i = 0; i < cities.size(); i++)
	{
		cout << cities.at(i) << endl;
	}

	cout << endl;

	// Prints a list of the edges.
	for(unsigned int i = 0; i < edgeList.size(); i++)
	{
		cout << edgeList.at(i) << endl;
	}

	graph.DFS("Dallas", dfs);


//	cout << endl;
//
//	for(unsigned int i = 0; i < dfs.size(); i++)
//	{
//		cout << dfs.at(i) << endl;
//	}

	return 0;
}
