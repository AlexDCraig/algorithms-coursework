/* Alex Hoffer: Parse a text file line by line and sort each line using stooge sort. Print the results to a file named "stooge.out". */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

ofstream insertOutput; // Our output file.

/* Alex's stoogesort: Given vector A, sort A[0...n-1] by
 * recursively sorting first two thirds, then second two thirds,
 * and then the first two thirds again by using the base case
 * of n = 2 and the lower index contains a higher value than
 * the higher index
 * Recurrence: T(n) = 3 * T(3n/2) + 1
 * Reasoning: 3 subproblems, each subproblem is of 3n/2 cost, with 1 indicating constant time operations
 */
void stoogeSort(vector <double>& vec, int low, int high)
{
	// Base case: n = 2, low element has higher value so swap
	if (vec.at(low) > vec.at(high))
	{
		double temp = vec.at(low);
		vec.at(low) = vec.at(high);
		vec.at(high) = temp;
	}

	// Recursive cases, n > 2
	if (high - low + 1 > 2)
	{
		int twoThirds = (high - low + 1) / 3; // ceiling(2n/3)
		
		// Recursive cases
		stoogeSort(vec, low, high - twoThirds); // sort first two thirds
		stoogeSort(vec, low + twoThirds, high); // sort second two thirds
		stoogeSort(vec, low, high - twoThirds); // sort first two thirds again
	}
}

// Sort the vectors in the vector and print out the results to the output file.
void processDoubleVec(vector < vector <double> > doubleVec)
{
	insertOutput.open("stooge.out");

	for (int i = 0; i < doubleVec.size(); i++)
	{
		vector <double> doubleVec2 = doubleVec.at(i);

		stoogeSort(doubleVec2, 0, doubleVec2.size() - 1);

		for (int j = 0; j < doubleVec2.size(); j++)
		{
			insertOutput << doubleVec2.at(j);

			if (j != doubleVec2.size() -1)
			{
				insertOutput << " ";
			}
		}

		insertOutput << "\n";
	}

	insertOutput.close();

}

int main()
{
	ifstream inputFile;
	inputFile.open("data.txt");
	vector < vector <double> > doubleVec;		
	string line;

	if (!inputFile)
	{
		cout << "Error opening file." << endl;
		return 1;
	}

	// Load data.txt line by line.
	// doubleVec is a vector that holds vectors of doubles that correspond to the file's lines.
	while (getline(inputFile, line))
	{
		// Parse the string.
		stringstream stream(line);

		vector <double> doubleVec2; 
		
		int counter = 0;

		while (1)
		{	
			double n;
			stream >> n; // Cast into double.
	
			if (stream && counter != 0) // We don't need the first umber for size reference since we're using vectors, so ignore it.
				doubleVec2.push_back(n);

			else if (!stream) // No more string to parse, break the infinite loop.
				break;		

			counter++;
		}

		doubleVec.push_back(doubleVec2);

	}

	inputFile.close();

	processDoubleVec(doubleVec);

	return 0;
}
