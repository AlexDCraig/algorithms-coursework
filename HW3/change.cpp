// Alex Hoffer: Use a dynamic programming algorithm to compute an array corresponding to how many of each coin type necessary
// for a minimum set that adds up to an amount desired. Additionally, compute total number of coins that correspond to this minimum.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

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

void adjustChangeResult(vector <int>& changeResult, vector <int> coins)
{
	vector <int> adjusted;

	for (int i = 0; i < changeResult.size(); i++)
		adjusted.push_back(0);

	for (int i = 0; i < coins.size(); i++)
	{
		int curValue = coins.at(i);
	
		for (int j = 0; j < changeResult.size(); j++)
		{
			if (changeResult.at(j) == curValue)
				adjusted.at(i) += 1;
		}
	}

	changeResult = adjusted;
}

// Find the vector of coins that were used
void findCoinsUsed(vector <int> coinsUsed, vector <int> coins, vector <int>& changeResult)
{
	int start = coinsUsed.size() - 1;

	while (start != 0)
	{
		int j = coinsUsed.at(start);
		changeResult.push_back(coins.at(j));
		start = start - coins.at(j);
	}

	reverse(changeResult.begin(), changeResult.end());

	adjustChangeResult(changeResult, coins);
}

// Returns minimum number of coins
int changeMaker(vector <int> coins, int amount, vector <int>& changeResult)
{
	int hugeValue = 100000000;
	vector <int> change(amount + 1);
	vector <int> coinsUsed(amount + 1);

	change.at(0) = 0;

	for (int i = 1; i <= amount; i++)
	{
		change.at(i) = hugeValue;
		coinsUsed.at(i) = -1;
	}

	for (int j = 0; j < coins.size(); j++)
	{
		for (int i = 1; i <= amount; i++)
		{
			if (i >= coins.at(j))
			{
				if (change.at(i - coins.at(j)) + 1 < change.at(i))
				{
					change.at(i) = 1 + change.at(i - coins.at(j));
					coinsUsed.at(i) = j;
				}
			}
		}
	}

	findCoinsUsed(coinsUsed, coins, changeResult);

	return change.at(amount);
}

void processVectors(vector < vector <int> > denominations, vector <int> amounts)
{
	vector < vector <int> > changeResults;
	vector <int> minNumCoinsNeeded;

	outputFile.open("change.txt");
	
	vector <int> changeResult;
	minNumCoinsNeeded.push_back(changeMaker(denominations.at(1), amounts.at(1), changeResult));
	changeResults.push_back(changeResult);

	vector <int> tmp;

	// Give denomination values to output file.
	tmp = denominations.at(1);

	for (int i = 0; i < tmp.size(); i++)
		outputFile << tmp.at(i) << " ";

	outputFile << endl;

	// Give the amount to output file.
	outputFile << amounts.at(1) << endl;

	// Give the change result array to the output file.
	tmp = changeResults.at(0); 

	for (int i = 0; i < tmp.size(); i++)
		outputFile << tmp.at(i) << " ";

	outputFile << endl;

	// Give the min number of coins used to the output file.
	outputFile << minNumCoinsNeeded.at(0) << endl;

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
