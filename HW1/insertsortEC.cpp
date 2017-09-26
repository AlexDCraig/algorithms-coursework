/* Alex Hoffer: Parse a text file line by line and sort each line using insertion sort. Print the results to a file named "insert.out". 
 * EXTRA CREDIT- Generate worst/best case input.
 * For insertion sort:
 Best case: Inputs are already sorted in ascending order.
Worst case: Inputs are sorted in Descending order.
*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void insertionSort(vector <int>& intVec)
{
	for (int i = 0; i < intVec.size(); i++) // Starting at second index, loop through the vector and compare the currently selected index to the indices before it.
	{
		int j = i;

		while (j > 0 && (intVec.at(j) < intVec.at(j - 1)))
		{
			int swapper = intVec.at(j);
			intVec.at(j) = intVec.at(j - 1);
			intVec.at(j - 1) = swapper;
			j -= 1;
		}
	}
}

// Generate random vectors.
void getIntVecs(vector < vector <int> >& intVec, int sizeOfEachVector, int sizeOfOverallVector, char* caseType)
{
	int intRange = 10001; // We want values from [0, 10000]

	bool isBest = true;

	if (strcmp(caseType, "best") == 0)
		isBest = true;

	else
		isBest = false;

	for (int i = 0; i < sizeOfOverallVector; i++)
	{
		vector <int> tempVec;
		int bestCaseNum = 0; 
		int worstCaseNum = 10000;

		for (int j = 0; j < sizeOfEachVector; j++)
		{
			if (isBest == true)
			{
				tempVec.push_back(bestCaseNum);
				bestCaseNum++;
			}
		
			else
			{
				tempVec.push_back(worstCaseNum);
				worstCaseNum--;
			}

		}	
	
		intVec.push_back(tempVec);
	}
}

// Sort the vectors in the vector and print out the results to the output file.
void processIntVec(vector < vector <int> > intVec)
{
	for (int i = 0; i < intVec.size(); i++)
	{
		vector <int> intVec2 = intVec.at(i);

		insertionSort(intVec2);
	}
}

int main(int argc, char* argv[])
{
	clock_t t;
	t = clock();

	if (argc != 3)
	{
		cout << "usage: " << argv[0] << " [sizeOfEachVector in int] [best | worst depending on what case you want] " << endl;
		exit(1);
	}

	int sizeOfEachVector = atoi(argv[1]); // Our n. How big will each vector be?
	int numVectorsToSort = 1000; // How many vectors of random ints should we make?
	char* caseType = argv[2];

	srand(time(NULL));

	vector < vector <int> > intVec;		

	insertOutput.open("insertTestEC.out", fstream::in | fstream::out | fstream::app);

	getIntVecs(intVec, sizeOfEachVector, numVectorsToSort, caseType);

	processIntVec(intVec);

	insertOutput << "**BEGIN**" << endl;
	insertOutput << "Size of each vector: " << sizeOfEachVector << endl;
	insertOutput << "Number of vectors sorted: " << numVectorsToSort << endl;
	insertOutput << "Best case or worst case: " << caseType << endl;
	t = clock() - t;
	float convertedTime = ((float)t)/(CLOCKS_PER_SEC);
	insertOutput << "Total runtime: " << convertedTime << " seconds " << endl;

	insertOutput << "**END**" << endl << endl;

	insertOutput.close();

	return 0;
}
