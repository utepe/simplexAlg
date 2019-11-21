#pragma once
#include <vector>

using namespace std;

class simplex
{
	private:
		vector<vector<double>> A;
		vector<double> B;
		vector<double> C;
		double maxZ;
		int numOfVariables;

	public:
		int rows;
		int columns;
		simplex(vector<vector<double>> a, vector<double> b, vector<double> c, int numVar);
		void runSimplexAlg();
		bool isOptimum();
		bool doSimplexCalc();
		int findPivotColumn();
		int findSmallestB(int pivotColumn);
		void doRowOperations(int pivotColumn, int pivotRow);
		void displayCurrent();
		void findMax();
};

