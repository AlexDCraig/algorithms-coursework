/* Alex Hoffer: Parse a text file line by line and sort each line using insertion sort. Print the results to a file named "insert.out". */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

ofstream insertOutput; // Our output file.

// Merge subroutine: We have two subarrays, one ranging from 0 to mid and one ranging from mid to max that are sorted. Let's merge them.
vector <double> merge(vector <double> firstSubarray, vector <double> secondSubarray)
{
	vector <double> sortedVector; // Where we'll place our results.
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

vector <double> mergeSort(vector <double> doubleVec)
{
	if (doubleVec.size() <= 1) // Base case: only one element in doubleVec, and so it is by definition sorted.
		return doubleVec;

	int halfIndex = ceil(doubleVec.size() / 2); // The midpoint of the overall array that separates the two subarrays is ceiling(n/2)

	// Set up vectors for the first subarray and second subarray using C++ vector iterators.
	vector <double> firstSubarray(doubleVec.begin(), doubleVec.begin() + halfIndex); // Starts at 0, ends at the midway point initially.
	vector <double> secondSubarray(doubleVec.begin() + halfIndex, doubleVec.end()); // Starts at midway point, ends at the last element.

	// Pass to merge the sorted versions of both subarrays
	// This statement will recursively call mergeSort on both subarrays until the base case of containing one element is reached.
	return merge(mergeSort(firstSubarray), mergeSort(secondSubarray));
}

// Sort the vectors in the vector and print out the results to the output file.
void processDoubleVec(vector < vector <double> > doubleVec)
{
	insertOutput.open("merge.out");

	for (int i = 0; i < doubleVec.size(); i++)
	{
		vector <double> doubleVec2 = doubleVec.at(i);

		vector <double> sortedVector = mergeSort(doubleVec2);

		for (int j = 0; j < sortedVector.size(); j++)
		{
			insertOutput << sortedVector.at(j);

			if (j != sortedVector.size() -1)
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
	
			if (stream)
			{
				if (counter != 0)
					doubleVec2.push_back(n);
			}

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
