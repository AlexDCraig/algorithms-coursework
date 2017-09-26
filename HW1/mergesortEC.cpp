/* Alex Hoffer: Analysis of merge sort algo. */
/* EXTRA CREDIT
 * Worst case: Inputs are random
 * Best case: Strictly increasing or strictly decreasing order
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
#include <math.h>
#include <string.h>

using namespace std;

ofstream insertOutput; // Our output file.

// Merge subroutine: We have two subarrays, one ranging from 0 to mid and one ranging from mid to max that are sorted. Let's merge them.
vector <int> merge(vector <int> firstSubarray, vector <int> secondSubarray)
{
	vector <int> sortedVector; // Where we'll place our results.
	int firstSubArrCount, secondSubArrCount; // We'll use the [] notation to access the proper index of the subarrays.
	firstSubArrCount = 0; // Start at 0, begin iterating thru both subarrays.
	secondSubArrCount = 0;

	int onFirstSubArr = false; // A T/F switch we'll use: is the right element to take right now on the first subarray? If so, switch to 1. If not, switch to 0.
	int totalSizeOfSortedArr = firstSubarray.size() + secondSubarray.size();	
	for (int j = 0; j < totalSizeOfSortedArr; j++)
	{
		if (firstSubArrCount < firstSubarray.size()) // Still more left in the first subarray.
		{
			if (secondSubArrCount < secondSubarray.size()) // Still room in the second subarray.
			{
				onFirstSubArr = (firstSubarray[firstSubArrCount] < secondSubarray[secondSubArrCount]); // Is the first subarray's element less than the second? If so, set this to true and we'll grab that element and put it into our sorted vector.
			}

			else // Seond sub array has already been traversed, focus on the first subarray.
			{
				onFirstSubArr = true;
			}
		}

		else
			onFirstSubArr = false; // First subarray has already been traversed.
		
		if (onFirstSubArr == true) // Focus on the first subarray.
		{
			sortedVector.push_back(firstSubarray[firstSubArrCount]);			
			if (firstSubArrCount < firstSubarray.size())
				firstSubArrCount += 1; // Move further into the first subarray.
		}

		else
		{
			sortedVector.push_back(secondSubarray[secondSubArrCount]);
			if (secondSubArrCount < secondSubarray.size())
				secondSubArrCount += 1;
		}
	}

	return sortedVector;
}

vector <int> mergeSort(vector <int> intVec)
{
	if (intVec.size() <= 1) // Base case: only one element in doubleVec, and so it is by definition sorted.
		return intVec;

	int halfIndex = ceil(intVec.size() / 2); // The midpoint of the overall array that separates the two subarrays is ceiling(n/2)

	// Set up vectors for the first subarray and second subarray using C++ vector iterators.
	vector <int> firstSubarray(intVec.begin(), intVec.begin() + halfIndex); // Starts at 0, ends at the midway point initially.
	vector <int> secondSubarray(intVec.begin() + halfIndex, intVec.end()); // Starts at midway point, ends at the last element.

	// Pass to merge the sorted versions of both subarrays
	// This statement will recursively call mergeSort on both subarrays until the base case of containing one element is reached.
	return merge(mergeSort(firstSubarray), mergeSort(secondSubarray));
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
		int bestCaseNum = 0; // If we want best case, we'll just do increasing order.

		for (int j = 0; j < sizeOfEachVector; j++)
		{
			if (isBest == true)
			{
				tempVec.push_back(bestCaseNum);
				bestCaseNum++;
			}

			else
			{
				int randInt = rand() % intRange;
				tempVec.push_back(randInt);
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
		mergeSort(intVec2);
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

	insertOutput.open("mergeTestEC.out", fstream::in | fstream::out | fstream::app);

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
