// Alex Hoffer: Use a dynamic programming algorithm to compute an array corresponding to how many of each coin type necessary
// for a minimum set that adds up to an amount desired. Additionally, compute total number of coins that correspond to this minimum.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

ofstream outputFile; // Our output file.

/*
// Sort the vectors in the vector and print out the results to the output file.
void processDoubleVec(vector < vector <int> > doubleVec)
{
	outputFile.open("stooge.out");

	for (int i = 0; i < doubleVec.size(); i++)
	{
		vector <int> doubleVec2 = doubleVec.at(i);

		//stoogeSort(doubleVec2, 0, doubleVec2.size() - 1);

		for (int j = 0; j < doubleVec2.size(); j++)
		{
			outputFile << doubleVec2.at(j);

			if (j != doubleVec2.size() -1)
			{
				outputFile << " ";
			}
		}

		outputFile << "\n";
	}

	outputFile.close();

}
*/

void processVectors(vector < vector <int> > denominations, vector <int> amounts)
{
	outputFile.open("change.txt");


	outputFile << "Hi";



	
	outputFile.close();
}

int main()
{
	ifstream inputFile;
	inputFile.open("amount.txt");
	vector < vector <int> > denominations;
	vector <int> amounts;		
	string line;

	if (!inputFile)
	{
		cout << "Error opening file." << endl;
		return 1;
	}

	int outerCounter = 0;
	bool isDenom; // Denominations are on lines 0, 2, 4... so either 0 or an even number. Amounts are on lines 1, 3, 5... so an odd number. 

	// Load  line by line.
	while (getline(inputFile, line))
	{
		if (outerCounter % 2 == 0 || outerCounter == 0)
			isDenom = true;

		else
			isDenom = false;

		// Parse the string.
		stringstream stream(line);

		vector <int> currentDenominations; 
		int currentAmount;

		int innerCounter = 0;

		while (1)
		{	
			int n;
			stream >> n; 
	
			if (stream)
			{
				if (isDenom == true) 
					currentDenominations.push_back(n);

				else if (isDenom == false)
					currentAmount = n;
			}

			else if (!stream) // No more string to parse, break the infinite loop.
				break;		

			innerCounter++;
		}

		if (isDenom == true)
			denominations.push_back(currentDenominations);

		else if (isDenom == false)
			amounts.push_back(currentAmount);

		outerCounter++;
	}

	inputFile.close();

	processVectors(denominations, amounts);

	return 0;
}
