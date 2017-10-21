#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

ofstream outputFile; // Our output file.

typedef struct activity
{
	int activityNumber;
	int startTime;
	int finishTime;
} ACTIVITY;

typedef struct activitySet
{
	int numberOfActivities;
	vector <ACTIVITY> activities;
} ACTIVITYSET;

void parseFile(vector <ACTIVITYSET>& activitySets, vector < vector <int> >& allLines)
{
	ACTIVITYSET* act1;
	int activitySetCounter = 0;
	
	for (int i = 0; i < allLines.size(); i++)
	{
		vector <int> temp = allLines.at(i);

		if (temp.size() == 1)
		{
			if (activitySetCounter == 0) // Just create
			{ 
				act1 = new ACTIVITYSET;
				act1->numberOfActivities = temp.at(0);
				activitySetCounter++;
			}

			else if (activitySetCounter != 0) // push previous one, create new one
			{
				activitySets.push_back(*act1);	
				act1 = new ACTIVITYSET;
				act1->numberOfActivities = temp.at(0);
			}
		}

		else if (temp.size() == 3)
		{
			ACTIVITY curActivity;
			curActivity.activityNumber = temp.at(0);
			curActivity.startTime = temp.at(1);
			curActivity.finishTime = temp.at(2);
			act1->activities.push_back(curActivity);
		}
	}

	activitySets.push_back(*act1);

	for (int i = 0; i < activitySets.size(); i++)
	{
		ACTIVITYSET tmp = activitySets.at(i);

		cout << "Activity Set " << i + 1 << " " << endl;
		cout << "Number of activities " << tmp.numberOfActivities << endl;

		vector <ACTIVITY> tmpAct = tmp.activities;

		for (int j = 0; j < tmpAct.size(); j++)
		{
			ACTIVITY tmpact1 = tmpAct.at(j);
			cout << "Activity number: " << tmpact1.activityNumber << endl;
			cout << "Start time: " << tmpact1.startTime << endl;
			cout << "Finish time: " << tmpact1.finishTime << endl;
		}
	}
}

int main()
{
	ifstream inputFile;
	inputFile.open("act.txt");
	vector <ACTIVITYSET> activitySets;
	string line;

	if (!inputFile)
	{
		cout << "Error opening file." << endl;
		return 1;
	}

	vector < vector < int > > allLines;

	// Load  line by line.
	while (getline(inputFile, line))
	{
		// Parse the string.
		stringstream stream(line);

		vector <int> lineInts;

		while (1)
		{
			int tmp;
			stream >> tmp;
			
			if (stream)
			{
				lineInts.push_back(tmp);		
			}

			else if (!stream) // No more string to parse, break the infinite loop.
			{
				allLines.push_back(lineInts);
				break;
			}
		}

	}

	parseFile(activitySets, allLines);

	inputFile.close();

	return 0;
}
