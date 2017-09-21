#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

ofstream insertOutput;

void processDoubleVec(vector < vector <double> > doubleVec)
{
	insertOutput.open("insert.out");

	for (int i = 0; i < doubleVec.size(); i++)
	{
		vector <double> doubleVec2 = doubleVec.at(i);

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

	while (getline(inputFile, line))
	{
		stringstream stream(line);

		vector <double> doubleVec2;
		
		while (1)
		{
			double n;
			stream >> n;
	
			if (stream)
				doubleVec2.push_back(n);

			else if (!stream)
				break;		
		}

		doubleVec.push_back(doubleVec2);

	}

	inputFile.close();

	processDoubleVec(doubleVec);

	return 0;
}
