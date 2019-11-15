#include <iostream>
#include <cmath>
#include <vector>
#include "simplex.h"

using namespace std;

int main() {
	//array of coeffiecents of all variables
	int columnSize = 8;
	int rowSize = 5;
	double A[5][8] = {
			{1, 1, 1, 1, 0, 0, 0, 0},
			{1, 0, 1, 0, 1, 0, 0, 0},
			{1, 0, 0, 0, 0, 1, 0, 0},
			{0, 1, 0, 0, 0, 0, 1, 0},
			{0, 0, 1, 0, 0, 0, 0, 1}
	};

	//array of constaint coefficients
	double B[] = { 5, 3, 4, 1, 2 };

	//array of constraints of the objective function
	double C[] = { 15, 6, 25, 0, 0, 0, 0, 0 };

	vector<vector<double>> vecA(rowSize, vector<double>(columnSize, 0));
	vector<double> vecB(columnSize);
	vector<double> vecC(columnSize);

	//store A as vector to be able to pass to class
	for (int i = 0; i < rowSize; i++) {
		for (int j = 0; j < columnSize; j++) {
			vecA[i][j] = A[i][j];
		}
	}

	//store B as vector to be able to pass to class
	for (int i = 0; i < rowSize; i++) {
		vecB[i] = B[i];
	}

	//stores C as vector to be able to pass to class
	for (int i = 0; i < columnSize; i++) {
		vecC[i] = C[i];
	}

	simplex simplex(vecA, vecB, vecC);
	simplex.runSimplexAlg();

}