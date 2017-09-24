/* Alex Hoffer: Parse a text file line by line and sort each line using insertion sort. Print the results to a file named "insert.out". */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

ofstream insertOutput; // Our output file.

/* An in-place sorting algorithm that follows the following procedure:
 * 	Given array A of length n:
 * 		- Let j = 0. 
 * 		- While j <= n
 * 			- Let key = A[j]
 * 			- Let i = j - 1
 * 			- While i > 0 and A[i] > key
 * 				- Let A[i + 1] = A[i]
 * 				- Decrement i
 * 			- Increment j
 * 			- Let A[i + 1] = key 
 */
void insertionSort(vector <double>& doubleVec)
{
	for (int i = 0; i < doubleVec.size(); i++) // Starting at second index, loop through the vector and compare the currently selected index to the indices before it.
	{
		int j = i;

		while (j > 0 && (doubleVec.at(j) < doubleVec.at(j - 1)))
		{
			double swapper = doubleVec.at(j);
			doubleVec.at(j) = doubleVec.at(j - 1);
			doubleVec.at(j - 1) = swapper;
			j -= 1;
		}
	}
}

// Sort the vectors in the vector and print out the results to the output file.
void processDoubleVec(vector < vector <double> > doubleVec)
{
	insertOutput.open("insert.out");

	for (int i = 0; i < doubleVec.size(); i++)
	{
		vector <double> doubleVec2 = doubleVec.at(i);

		insertionSort(doubleVec2);

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
