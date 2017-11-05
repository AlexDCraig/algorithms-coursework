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
	string team;
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
		vertex.team + "";
		vertex.name = vertexNames.at(i);
		vertex.color = "WHITE";
		vertex.d = 0;
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

void createAdjacencyList(GRAPH* G)
{
	vector < vector <int> > tempAdjList;

	for (int i = 0; i < G->Vertices.size(); i++)
	{
		vector <int> list;
		V curVertex = G->Vertices.at(i);
		
		for (int j = 0; j < G->Edges.size(); j++)
		{
			E tmpEdge = G->Edges.at(j);
			V vertex1 = tmpEdge.v1;
			V vertex2 = tmpEdge.v2;

			if (curVertex.name == vertex1.name)
			{
				int vertex2Index = findVertex(G, vertex2.name);
				list.push_back(vertex2Index);
			}

			else if (curVertex.name == vertex2.name)
			{
				int vertex1Index = findVertex(G, vertex1.name);
				list.push_back(vertex1Index);
			}
		}

		tempAdjList.push_back(list);
	}

	G->AdjList = tempAdjList;
}

void printGraph(GRAPH* g)
{
	cout << "***VERTICES***" << endl;

	for (int i = 0; i < g->Vertices.size(); i++)
	{
		cout << g->Vertices.at(i).name << " " << g->Vertices.at(i).color << " " << g->Vertices.at(i).d;
		
		V* tmp = g->Vertices.at(i).p;

		if (tmp != NULL)
			cout << " " << tmp->name;

		cout << endl;
	}

	cout << endl;		

	cout << "***EDGES***" << endl;

	for (int i = 0; i < g->Edges.size(); i++)
	{
		E edge1 = g->Edges.at(i);
		cout << edge1.v1.name << " ---- " << edge1.v2.name;
		cout << endl;
	}
}

void printAdjacencyList(GRAPH* g)
{
	cout << "***ADJACENCY LIST***" << endl;
	
	for (int i = 0; i < g->AdjList.size(); i++)
	{
		vector <int> tmp = g->AdjList.at(i);
		
		cout << i;

		for (int j = 0; j < tmp.size(); j++)
		{
			cout << " --> " << tmp.at(j) << " ";		
		}

		cout << endl;
	}
}

void BFS(GRAPH* G)
{
	vector <int> Q; // Our queue. Initialize it to 0, which is the first index of our vertices.
	Q.push_back(0);	
	int size = 1;

	while (Q.size() > 0)
	{
		int u = Q.at(0); 
		Q.erase(Q.begin());
		
		V* currentNode = &(G->Vertices.at(u));
		vector <int> tmpAdjList = G->AdjList.at(u);

		for (int i = 0; i < tmpAdjList.size(); i++)
		{
			int neighboringIndex = tmpAdjList.at(i);	
			V* v = &(G->Vertices.at(neighboringIndex));
			
			if (v->color == "WHITE")
			{
				v->color = "GREY";
				v->d = currentNode->d + 1;
				v->p = currentNode;	
				Q.push_back(neighboringIndex);
			}	
		}

		currentNode->color = "BLACK";
	}
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

	inputFile.close();

	GRAPH* graph = drawGraph(numWrestlers, wrestlerNames, numRivalries, rivalries);
	createAdjacencyList(graph);	
	BFS(graph);
	printGraph(graph);
	printAdjacencyList(graph);	

	return 0;
}
