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
}


vector <int> getActivityNumbers(ACTIVITYSET actSet)
{
	vector <ACTIVITY> activities = actSet.activities;
	vector <int> activityNumbers;

	for (int i = 0; i < activities.size(); i++)
		activityNumbers.push_back(activities.at(i).activityNumber);

	return activityNumbers;
}

vector <int> getStartTimes(ACTIVITYSET actSet)
{
	vector <ACTIVITY> activities = actSet.activities;
	vector <int> startTimes;

	for (int i = 0; i < activities.size(); i++)
		startTimes.push_back(activities.at(i).startTime);

	return startTimes;

}

vector <int> getFinishTimes(ACTIVITYSET actSet)
{
	vector <ACTIVITY> activities = actSet.activities;
	vector <int> finishTimes;

	for (int i = 0; i < activities.size(); i++)
		finishTimes.push_back(activities.at(i).finishTime);

	return finishTimes;
}


bool sortFunction(ACTIVITY i, ACTIVITY j)
{
	return i.finishTime > j.finishTime;
}

void Greedy_Activity_Selector(vector <int> startTimes, vector <int> finishTimes)
{
	vector <int> chosenActivities;
	int n = startTimes.size();
	int i = 0;

	chosenActivities.push_back(i);

	for (int j = 1; j < n; j++)
	{
		if (finishTimes.at(j) <= startTimes.at(i))
		{
			chosenActivities.push_back(j);
			i = j; 
		}
	}

	cout << "Number of activities selected = " << chosenActivities.size() << endl;
	
	cout << "Activities: ";

	for (int i = 0; i < chosenActivities.size(); i++)
		cout << chosenActivities.at(i) << " ";

	cout << endl;
	cout << endl;
}

void processActivitySets(vector <ACTIVITYSET> activitySets)
{
	for (int i = 0; i < activitySets.size(); i++)
	{
		cout << "Set " << i + 1 << endl;

		ACTIVITYSET tmp = activitySets.at(i);
		
		// sort tmp.activities.begin(), tmp.activities.end() by finish time decreasing
		sort(tmp.activities.begin(), tmp.activities.end(), sortFunction);

		//vector <int> activityNumbers = getActivityNumbers(tmp);
		vector <int> startTimes = getStartTimes(tmp);
		vector <int> finishTimes = getFinishTimes(tmp); 

		Greedy_Activity_Selector(startTimes, finishTimes);
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

	processActivitySets(activitySets);

	inputFile.close();

	return 0;
}
