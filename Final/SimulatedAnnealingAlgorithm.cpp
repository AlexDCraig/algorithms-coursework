#include <cstdio>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;
typedef vector<int> candidate;

ifstream inputFile;
ofstream outputFile;
string outputFileName;

class Data {
public:
	vector< pair<double,double> > cityCoords;
	vector< vector<double> > cost;
	vector <int> cityNumbers;
	vector <int> xCoordinates;
	vector <int> yCoordinates;
	int** adjacencyMatrix;
	int N;
	char s[30];

	Data() {

			string line;
			if (!inputFile)
			{
				cout << "Error opening file." << endl;
				exit(1);
			}

			// Load  line by line.
			while (getline(inputFile, line))
			{
				int counter = 0;

				// Parse the string.
				stringstream stream(line);
		
				while (1)
				{
					int tmp;
					stream >> tmp;

					if (stream)
					{
						if (counter == 0)
							cityNumbers.push_back(tmp);

						else if (counter == 1)
							xCoordinates.push_back(tmp);
	
						else if (counter == 2)
							yCoordinates.push_back(tmp);
					}		

					else if (!stream) // No more string to parse, break the infinite loop.
					{
						break;
					}

					counter++;
				}		
			}


		// N cities
	//	scanf("%s",s);
	//	scanf("%d",&N);
	
		N = cityNumbers.size();
		
		// index from 1
		cityCoords.push_back(make_pair(0,0));
		vector< double> T;
		cost.push_back(T);

		for(int i=0;i<N;i++) {
			double x,y;
			//scanf("%lf%lf",&x,&y);
			//cityCoords.push_back(make_pair(x,y));
			cityCoords.push_back(make_pair(xCoordinates.at(i), yCoordinates.at(i)));
		}

		constructAdjacencyMatrix();

		for(int i=0;i<N;i++) {
			vector<double> V(N+1);
			for(int j = 1;j<N;j++) {
				//scanf("%lf",&V[j]);
				V[j] = adjacencyMatrix[i][j];
			}
			cost.push_back(V);
		}
	}

	int computeDistance(int idx1, int idx2)
	{
		int x1 = xCoordinates.at(idx1);
		int x2 = xCoordinates.at(idx2);
		int y1 = yCoordinates.at(idx1);
		int y2 = yCoordinates.at(idx2);

		float firstClause = x1 - x2;
		firstClause = pow(firstClause, 2);
		float secondClause = y1 - y2;
		secondClause = pow(secondClause, 2);
		float sumOfClauses = firstClause + secondClause;
		float distance = sqrt(sumOfClauses);

		distance = round(distance);

		return distance;
	}

	void constructAdjacencyMatrix()
	{
		int max = cityNumbers.size();
		adjacencyMatrix = new int*[max];

		for (int i = 0; i < cityNumbers.size(); i++)
		{
			adjacencyMatrix[i] = new int[max];

			for (int j = 0; j < cityNumbers.size(); j++)
			{
				adjacencyMatrix[i][j] = computeDistance(i, j);
			}	
		}
	}

	static int myrandom (int i) { return rand()%i;}

	candidate genRand(candidate C) {
		int l,a,b,temp;
		l = C.size();
		a = rand()%l;
		b = rand()%l;
		temp = C[a];
		C[a] = C[b];
		C[b] = temp;
		return C;
	}

	double evaluate(candidate C) {
		return tourCost(C);
	}

	double tourCost(candidate C) {
		int l = C.size();
		double tourCost = 0.0;
		l = l-1;
		for (int i=0;i <l; i++) {
			tourCost += cost[C[i]][C[i+1]];
		}
		tourCost += cost[C[l]][C[0]];
		return tourCost;
	}

	void print(candidate C) {
		for(int i=0;i<C.size();i++)
			printf("%d ",C[i]);
		printf("\n");
	}
};

class SimulatedAnnealing {
public:
	candidate best;
	double minTour;
	Data data;

	SimulatedAnnealing() {
		minTour = 0.0;
	} 
	double randProb()
	{
			double p = (rand() / (RAND_MAX + 1.0));
	    return p;
	}
	void run() {
		vector <int> V(data.N);
		for (int i=0;i < data.N;i++) {
			V[i] = i+1;
		}
		candidate c = data.genRand(V);
		best = c;
		minTour = data.tourCost(c);
		for(int i=0;i<1000;i++) {
			random_shuffle(c.begin(),c.end());
			double tCost = data.tourCost(c);
			if(tCost < minTour) {
				minTour = tCost;
				best = c;
			}
		}
		c = best;
		double p,expP,deltaE;
		double Temp = 1000000000;
		for(double T=Temp;T > 0.01;T*=0.5) {
			for(int i=0;i<100000;i++) {
				candidate n = data.genRand(c);
				//data.print(n);
				deltaE = eval(c) - eval(n);
				deltaE /= T;
				p = 1 / (1+exp(-1*deltaE));
				expP = randProb();
				// printf("p : %lf , expP : %lf\n",p,expP);
				if(expP < p) { // move
					c = n;
					double tCost = data.tourCost(c);
					if(tCost < minTour ) {
						best = c;
						
						minTour = tCost;
					}
				}	
			}
		}
		
		
		twoOpt();
		

	/*	outputFile.open(outputFileName.c_str());
		outputFile << minTour << "\n";
	
		for (int i = 0; i < best.size(); i++)
			outputFile << best.at(i)-1 << "\n";

		outputFile.close();
//		data.print(best);
//		printf("%lf\n", minTour); */
	}

	void twoOpt()
	{
		bool changed;

		do {
			changed = false;
			
			for (int i = 0; i < best.size() - 4; i++)
			{
				for (int j = i + 3; j < best.size() - 4; j++)
				{
					int distance1 = data.computeDistance(best.at(i) -1, best.at(i + 1) -1);
					int distance2 = data.computeDistance(best.at(j-1) -1, best.at(j)-1);
					int distance3 = data.computeDistance(best.at(i)-1, best.at(j-1)-1);
					int distance4 = data.computeDistance(best.at(i+1)-1, best.at(j)-1);

					if ((distance1 + distance2) > (distance3 + distance4))
					{
						reverse(best.begin() + i + 1, best.begin() + j);
						changed = true;
					}
				}
			}
		}
		while (changed); 

		twoHalfOpt();
	}

	void twoHalfOpt()
	{
		bool changed;

		do
		{
			changed = false;
		
			for (int i = 0; i < best.size() - 4; i++)
			{
				for (int j = i + 3; j < best.size() - 4; j++)
				{
					int option1current = (data.computeDistance(best.at(i) - 1, best.at(i+1) - 1)) + (data.computeDistance(best.at(i+1)-1, best.at(i+2)-1)) + (data.computeDistance(best.at(j-1)-1, best.at(j)-1));
					int option1Check = (data.computeDistance(best.at(i)-1, best.at(i+2)-1)) + (data.computeDistance(best.at(j-1) -1, best.at(i+1)-1)) + (data.computeDistance(best.at(i+1) -1, best.at(j)-1));

					if (option1Check < option1current)
					{
						int temp = best.at(i+1);
						for (int m = i + 2; m < j; m++)
							best.at(m-1) = best.at(m);
						best.at(j-1) = temp;
						changed = true;
					}

					int option2current = (data.computeDistance(best.at(i)-1, best.at(i+1)-1)) + (data.computeDistance(best.at(j-2)-1, best.at(j-1)-1)) + (data.computeDistance(best.at(j-1)-1, best.at(j)-1));
					int option2Check = (data.computeDistance(best.at(i)-1, best.at(j-1)-1)) + (data.computeDistance(best.at(j-1)-1, best.at(i+1)-1)) + (data.computeDistance(best.at(j-2)-1, best.at(j)-1));
					
					if (option2Check < option2current)
					{
						int temp = best.at(j-1);							
							
						for (int m = j -2; m > i; m--)
							best.at(m+1) = best.at(m);
						
						best.at(i+1) = temp;
						changed = true;
					}
				}
			}

		} while (changed);

		calculatePathDistance();
	}

	void calculatePathDistance()
	{
		int result = 0;

		for (int i = 0; i < best.size() - 2; i++)
			result += data.computeDistance(best.at(i)-1, best.at(i + 1)-1);

		result += data.computeDistance(best.at(0)-1, best.at(best.size() - 1)-1);
  		minTour = result;
		outputToFile();
	}

	void outputToFile()
	{
		cout << best.size() << endl;
		outputFile.open(outputFileName.c_str());
		outputFile << minTour << "\n";
	
		for (int i = 0; i < best.size(); i++)
			outputFile << best.at(i)-1 << "\n";

		outputFile.close();
	}


	double eval(candidate C) {
		return data.evaluate(C);
	}

};

int main(int argc, char* argv[]) {
	inputFile.open(argv[1]);
	string firstPart(argv[1]);	
	outputFileName = firstPart + ".AlexHoffer.tour";	
	time_t sysTime;
	srand(time(&sysTime));
	SimulatedAnnealing SA;
	SA.run();
	return 0;
}
