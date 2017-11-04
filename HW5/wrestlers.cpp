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

vector <string> colors;

typedef struct V
{
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

void printVector(vector <string> a)
{
	for (int i = 0; i < a.size(); i++)
		cout << a.at(i) << " ";

	cout << endl;
}

int main(int argc, char* argv[])
{
	colors.push_back("WHITE");
	colors.push_back("GREY");
	colors.push_back("BLACK");

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

	return 0;
}
