// Alex Hoffer: Use a dynamic programming algorithm to compute an array corresponding to how many of each coin type necessary
// for a minimum set that adds up to an amount desired. Additionally, compute total number of coins that correspond to this minimum.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

ofstream outputFile; // Our output file.

// We have a list of the numbers we've combined to get our result in changeResult
// Now, map these to the coins to produce the output format requested.
void adjustChangeResult(vector <int>& changeResult, vector <int> coins)
{
	vector <int> adjusted;
	int adjustedIndex = 0;

	for (int i = 0; i < coins.size(); i++)
		adjusted.push_back(0);

	// Loop through all possible coins.
	// For each coin, loop through the change result and if the coin is a match, increment the corresponding index's value.
	for (int i = 0; i < coins.size(); i++)
	{
		int curValue = coins.at(i);
	
		for (int j = 0; j < changeResult.size(); j++)
		{
			if (changeResult.at(j) == curValue)
			{
				adjusted.at(i) += 1;
			}
		}
	}

	changeResult = adjusted;
}

// Find the vector of coins that were combined to reach our solution
bool findCoinsUsed(vector <int> coinsUsed, vector <int> coins, vector <int>& changeResult)
{
	// Start from the end...
	int start = coinsUsed.size() - 1;

	if (coinsUsed.at(coinsUsed.size() - 1) == -1)
	{
		return false;
	}

	while (start != 0)
	{
		// Map the coinsUsed vector to their corresponding coin.
		int j = coinsUsed.at(start);
		changeResult.push_back(coins.at(j));
		start = start - coins.at(j);
	}

	// We started at the end, so reverse the vector.
	reverse(changeResult.begin(), changeResult.end());

	// Get it in the right form.
	adjustChangeResult(changeResult, coins);

	return true;
}

// Returns minimum number of coins
int changeMaker(vector <int> coins, int amount, vector <int>& changeResult)
{
	int hugeValue = 100000000;
	vector <int> change(amount + 1);
	vector <int> coinsUsed(amount + 1);

	change.at(0) = 0; // Having an amount of 0 means we used 0 coins.

	for (int i = 1; i <= amount; i++)
	{
		change.at(i) = hugeValue; // The equivalent of inf.
		coinsUsed.at(i) = -1; // To indicate we didn't use this coin yet.
	}

	// Think of this as a table of coins by increasing amounts until the amount we want
	// If a coin is not greater than in value than the current max amount, make a decision to include it or not
	for (int j = 0; j < coins.size(); j++)
	{
		for (int i = 1; i <= amount; i++)
		{
			if (i >= coins.at(j))
			{
				if (change.at(i - coins.at(j)) + 1 < change.at(i))
				{
					change.at(i) = 1 + change.at(i - coins.at(j));
					coinsUsed.at(i) = j; // We used the coin at index j, map it over later
				}
			}
		}
	}

	// Map coin indices to actual coins.
	bool success = findCoinsUsed(coinsUsed, coins, changeResult);

	if (success == false)
		outputFile << "Problem without solution provided." << endl;

	return change.at(amount);
}

void processVectors(vector < vector <int> > denominations, vector <int> amounts)
{
	vector < vector <int> > changeResults;
	vector <int> minNumCoinsNeeded;

	// Get results for each denomination set and amount.
	for (int i = 0; i < denominations.size(); i++)
	{
		vector <int> changeResult;
		minNumCoinsNeeded.push_back(changeMaker(denominations.at(i), amounts.at(i), changeResult));
		changeResults.push_back(changeResult);
	}

/*	
	// The output file will match the denominations and amounts but add two lines for each one.
	int maxLines = 2 * (denominations.size() + amounts.size());

	int printCounter = 0;
	int denomCounter = 0;
	int amtCounter = 0;
	int resultCounter = 0;
	int minCoinCounter = 0;

	// Printing out to output file in the order [ denom, amount, result vector, min number of coins ]
	for (int i = 0; i < maxLines; i++)
	{
		vector <int> temp;

		if (printCounter == 0)
		{
			temp = denominations.at(denomCounter);

			for (int i = 0; i < temp.size(); i++)
			{
				outputFile << temp.at(i) << " ";
			}

			outputFile << endl;

			denomCounter += 1;
		}	

		else if (printCounter == 1)
		{
			outputFile << amounts.at(amtCounter) << endl;
			amtCounter += 1;
		}

		else if (printCounter == 2)
		{
			temp = changeResults.at(resultCounter);
			
			for (int i = 0; i < temp.size(); i++)
			{
				outputFile << temp.at(i) << " ";
			}

			outputFile << endl;

			resultCounter += 1;
		}

		else if (printCounter == 3)
		{		
			outputFile << minNumCoinsNeeded.at(minCoinCounter) << endl;
			minCoinCounter += 1;
		}

		printCounter += 1;

		if (printCounter == 4)
			printCounter = 0;
	}
*/

	outputFile << "# of amounts and vectors = " << amounts.size() << endl;

}

void generateAmounts(vector <int>& amounts)
{
	int amount = 16000;

	outputFile << "Amount to make change for: " << amount << endl;

	for (int i = 0; i < 100; i++)
	{
		amounts.push_back(amount);
	}
}

void generateDenominations(vector < vector <int> >& denominations, vector <int> amounts)
{
	int valueCount = 8000;

	outputFile << "# of values in each denomination set: " << valueCount << endl;

	for (int i = 0; i < 100; i++)
	{
		vector <int> denomination;

		denomination.push_back(1);

		for (int j = 0; j < valueCount - 1; j++)
		{
			int coin = rand() % amounts.at(i) + 1;
			denomination.push_back(coin);
		}

		denominations.push_back(denomination);
	}
}

int main()
{
	srand(time(NULL));

	outputFile.open("test.txt");

	clock_t time;	

	vector < vector <int> > denominations;
	vector <int> amounts;	
		
	generateAmounts(amounts);
	generateDenominations(denominations, amounts);
	
	time = clock();

	processVectors(denominations, amounts);

	time = clock() - time;	

	float convertedTime = ((float)time)/(CLOCKS_PER_SEC);
	
	outputFile << convertedTime << " seconds" << endl;

	outputFile.close();

	return 0;
}
