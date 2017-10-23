/* Alex Hoffer: Activity Selection Last-to-Start
 * Algorithm is Theta(n log n) because of vector sorting
 * Greedy algorithm where given an input of activities sorted by decreasing finish time, we (1) pop the first element off the set and put it in our schedule and then (2) we pop each successive activity off the set and if it is compatible with our schedule, then we add it to our schedule
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
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

// Merge subroutine: We have two subarrays, one ranging from 0 to mid and one ranging from mid to max that are sorted. Let's merge them.
vector <ACTIVITY> merge(vector <ACTIVITY> firstSubarray, vector <ACTIVITY> secondSubarray)
{
	vector <ACTIVITY> sortedVector; // Where we'll place our results.
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
				onFirstSubArr = (firstSubarray[firstSubArrCount].finishTime > secondSubarray[secondSubArrCount].finishTime); // Is the first subarray's element greater than the second? If so, set this to true and we'll grab that element and put it into our sorted vector.
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

vector <ACTIVITY> mergeSort(vector <ACTIVITY> activities)
{
	if (activities.size() <= 1) // Base case: only one element in doubleVec, and so it is by definition sorted.
		return activities;

	int halfIndex = ceil(activities.size() / 2); // The midpoint of the overall array that separates the two subarrays is ceiling(n/2)

	// Set up vectors for the first subarray and second subarray using C++ vector iterators.
	vector <ACTIVITY> firstSub(activities.begin(), activities.begin() + halfIndex);
	vector <ACTIVITY> secondSub(activities.begin() + halfIndex, activities.end());

	// Pass to merge the sorted versions of both subarrays
	// This statement will recursively call mergeSort on both subarrays until the base case of containing one element is reached.
	return merge(mergeSort(firstSub), mergeSort(secondSub));
}

// Process the input file by the following strategy:
// (1) If there is one value on a line, it is the beginning of a new activity set.
// 	(1a) If there has never been 1 value on a line before, then this is the 	first activity set and so we don't push anything, we just create.
// 	(1b) If this is not the first activity set, then we push the previous
// 	activity set and create a new one.
//
// (2) If there are three values on a line, it is an activity that falls within the current activity set. 
// (3) Upon exiting, push the last accumulated activity set into our set of activity sets 
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

/* Helper functions to maintain three separate sets for activity Numbers, start times, and finish times. The three sets map to each other via index. */
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

// Helper function to sort our activity vector by decreasing finish time.
bool sortFunction(ACTIVITY i, ACTIVITY j)
{
	return i.finishTime > j.finishTime;
}

// Greedy algorithm where you choose the last finishing activity at each choice and then include it in a schedule of activities if and only if it does not overlap with previously chosen activities.
void Greedy_Activity_Selector(vector <int> activityNumbers, vector <int> startTimes, vector <int> finishTimes)
{
	vector <int> chosenActivities;
	int n = startTimes.size();
	int i = 0;

	chosenActivities.push_back(activityNumbers.at(i));

	for (int j = 1; j < n; j++)
	{
		if (finishTimes.at(j) <= startTimes.at(i))
		{
			chosenActivities.push_back(activityNumbers.at(j));
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

// Given a set of all activity sets, process them like so:
// Sort each activity set from the activity with the latest finish time to the activity with the earliest finish time
// Given a sorted activity set, process the activityNumbers, startTimes, and finishTimes into separate sets.
// Pass each of these sets into our Greedy Activity Selector algorithm to get an optimally maximum number of compatible activities and a list of such activities.
void processActivitySets(vector <ACTIVITYSET> activitySets)
{
	for (int i = 0; i < activitySets.size(); i++)
	{
		cout << "Set " << i + 1 << endl;

		ACTIVITYSET tmp = activitySets.at(i);
		
		// sort tmp.activities.begin(), tmp.activities.end() by finish time decreasing
		// sort(tmp.activities.begin(), tmp.activities.end(), sortFunction);

		tmp.activities = mergeSort(tmp.activities);

		vector <int> activityNumbers = getActivityNumbers(tmp);
		vector <int> startTimes = getStartTimes(tmp);
		vector <int> finishTimes = getFinishTimes(tmp); 

		Greedy_Activity_Selector(activityNumbers, startTimes, finishTimes);
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

	// Use a vector of vectors to collect the ints from each line.
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
