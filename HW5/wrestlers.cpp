#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
using namespace std;

ofstream outputFile; // Our output file.

typedef struct V
{
	string name;
	string color; // Color of vertex.
	int d; // Distance of vertex from source.
	V* p; // Pointer to predecessor vertex.
} V;

typedef struct E
{
	V v1; // The first vertex in an edge.
	V v2; // The second.
} E;

typedef struct graph
{
	vector <V> Vertices; // V = {v1, v2... vn}
	vector <E> Edges; // E = { (v1,v2), (v2,v3)... }
	vector < vector < int > > AdjList;
} GRAPH;

// Given graph G and a wrestler's nane, find the index of his vertex.
int findVertex(GRAPH* G, string wrestName)
{
	vector <V> tmpVertices = G->Vertices;

	for (int i = 0; i < tmpVertices.size(); i++)
	{
		if (tmpVertices.at(i).name == wrestName)
			return i;
	}

	return -1;
}

GRAPH* drawGraph(int numVertices, vector <string> vertexNames, int numEdges, vector < vector < string > > edges)
{
	GRAPH* graph = new GRAPH;

	for (int i = 0; i < numVertices; i++)
	{
		V vertex;
		vertex.name = vertexNames.at(i);
		vertex.color = "WHITE";
		vertex.d = -1;
		vertex.p = NULL;
		graph->Vertices.push_back(vertex);
	}

	edges.erase(edges.begin());

	for (int i = 0; i < edges.size(); i++)
	{
		vector <string> vertices = edges.at(i);
		E edge;
		int vertex1 = findVertex(graph, vertices.at(0));
		int vertex2 = findVertex(graph, vertices.at(1));
		edge.v1 = graph->Vertices.at(vertex1);
		edge.v2 = graph->Vertices.at(vertex2);
		graph->Edges.push_back(edge);
	}

	return graph;
}

void printGraph(GRAPH* g)
{
	
}

int main(int argc, char* argv[])
{
	int numWrestlers = 0;
	bool onNumWrestlers = true;
	vector <string> wrestlerNames;
	bool onWrestlerNames = false;
	int numRivalries = 0;
	bool onNumRivalries = false;
	vector < vector < string > > rivalries;
	bool onRivalries = false;
	int counter = 1;

	ifstream inputFile;
	inputFile.open(argv[1]);
	
	string line;

	if (!inputFile)
	{
		cout << "Error opening file." << endl;
		return 1;
	}

	// Use a vector of vectors to collect the ints from each line.
	// Load  line by line.
	while (getline(inputFile, line))
	{
		// Parse the string.
		stringstream stream(line);

		vector <string> rivalry;

		if (onWrestlerNames)
		{
			if (counter > numWrestlers)
			{
				onWrestlerNames = false;
				onNumRivalries = true;
				counter = 0;
			}
		}

		else if (onRivalries)
		{
			if (counter > numRivalries)
			{
				onRivalries = false;	
				rivalries.push_back(rivalry);
				counter = 1;
			}
		}
				
		while (1)
		{
			int tmp;
			string stringTmp;

			if (onNumWrestlers || onNumRivalries)
				stream >> tmp;

			else 
				stream >> stringTmp;

			if (stream)
			{
				if (onNumWrestlers)
				{
					numWrestlers = tmp;		
					onNumWrestlers = false;
					onWrestlerNames = true;
				}

				else if (onWrestlerNames)
				{
					wrestlerNames.push_back(stringTmp);
					counter++;
				}

				else if (onNumRivalries)
				{
					numRivalries = tmp;
					onNumRivalries = false;
					onRivalries = true;
				}

				else if (onRivalries)
				{
					rivalry.push_back(stringTmp);
				}
			}

			else if (!stream) // No more string to parse, break the infinite loop.
			{
				break;
			}
		}

		if (onRivalries)
		{
			rivalries.push_back(rivalry);
			counter++;
		}
		
	}

	GRAPH* graph = drawGraph(numWrestlers, wrestlerNames, numRivalries, rivalries);

	inputFile.close();

	return 0;
}
