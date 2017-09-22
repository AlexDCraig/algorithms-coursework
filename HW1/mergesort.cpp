/* Alex Hoffer: Parse a text file line by line and sort each line using insertion sort. Print the results to a file named "insert.out". */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

ofstream insertOutput; // Our output file.

// Merge subroutine: We have two subarrays, one ranging from 0 to mid and one ranging from mid to max that are sorted. Let's merge them.
void merge(vector <double>& doubleVec, int lowIndex, int maxIndex, int halfIndex)
{
	for (int i = 0; i < doubleVec.size(); i++)
		cout << doubleVec.at(i);



}

void mergeSort(vector <double>& doubleVec, int lowIndex, int maxIndex)
{
	int halfIndex;

	if (lowIndex < maxIndex) // Stop when n is one (only 1 element, which by definition is sorted), this is our n = 1 base case
	{
		halfIndex = (lowIndex + maxIndex) / 2; // Ceiling of n/2.
		
		// Split vector into two halves
		// Recursively sort each half by continuously breaking the half at hand until it is a single element (by definition sorted)
		mergeSort(doubleVec, lowIndex, halfIndex); // Sort the lower half.
		mergeSort(doubleVec, halfIndex + 1, maxIndex); // Sort the higher half.
		merge(doubleVec, lowIndex, maxIndex, halfIndex); // Call our merge routine.

	}
	
}

// Sort the vectors in the vector and print out the results to the output file.
void processDoubleVec(vector < vector <double> > doubleVec)
{
	insertOutput.open("merge.out");

	for (int i = 0; i < doubleVec.size(); i++)
	{
		vector <double> doubleVec2 = doubleVec.at(i);

		mergeSort(doubleVec2, 0, doubleVec2.size() - 1);

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
		
		while (1)
		{
			double n;
			stream >> n; // Cast into double.
	
			if (stream)
				doubleVec2.push_back(n);

			else if (!stream) // No more string to parse, break the infinite loop.
				break;		
		}

		doubleVec.push_back(doubleVec2);

	}

	inputFile.close();

	processDoubleVec(doubleVec);

	return 0;
}
