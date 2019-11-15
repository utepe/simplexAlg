#pragma once
#include <vector>

using namespace std;

class simplex
{
	private:
		int rows;
		int columns;
		vector<vector<double>> A;
		vector<double> B;
		vector<double> C;
		double max;

	public:
		simplex(vector<vector<double>> a, vector<double> b, vector<double> c);
		bool isOptimum();
		bool doSimplexCalc();
		void runSimplexAlg();
		int findPivotColumn();
		int findSmallestB(int pivotColumn);
		void displayCurrent();
		void findMax();
};

