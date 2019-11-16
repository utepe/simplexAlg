#include <iostream>
#include <cmath>
#include <vector>
#include "simplex.h"

using namespace std;

simplex::simplex(vector<vector<double>> a, vector<double> b, vector<double> c) {
	maxZ = 0;
	columns = a[0].size();
	rows = a.size();

	//initialize A vector
	A.resize(rows, vector<double>(columns, 0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			A[i][j] = a[i][j];
		}
	}

	//initialize B vector
	for (int i = 0; i < b.size(); i++) {
		B.push_back(b[i]);
	}

	//initialize C vector
	for (int i = 0; i < c.size(); i++) {
		C.push_back(c[i]);
	}
}

void simplex::runSimplexAlg() {
	bool run = isOptimum();

	do{
		bool solution = doSimplexCalc();
		if (solution) {
			break;
		}
	} while (!run);
	
}

bool simplex::isOptimum() {
	for (int i = 0; i < C.size(); i++) {
		if (C[i] > 0) {
			return false;
		}
	}

	return true;
}

bool simplex::doSimplexCalc() {
	if (isOptimum()) {
		return true;
	}

	int pivotColumn = findPivotColumn();
	int pivotRow = findSmallestB(pivotColumn);
	doRowOperations(pivotColumn, pivotRow);

	return false;
}

int simplex::findPivotColumn() {
	int max = -9999999;
	int index = 0;

	for (int i = 0; i < C.size(); i++) {
		if (C[i] >= max) {
			max = C[i];
			index = i;
		}
	}
	return index;
}

int simplex::findSmallestB(int pivotColumn) {
	double min = 9999999;
	int index = 0;

	for (int i = 0; i < B.size(); i++){
		if (B[i] / A[i][pivotColumn] < min) {
			min = (B[i] / A[i][pivotColumn]);
			index = i;
		}
	}

	return index;
}

void simplex::doRowOperations(int pivotColumn, int pivotRow) {
	double pivotMultiplier = A[pivotRow][pivotColumn];

	maxZ -= (C[pivotColumn] * (B[pivotRow] / pivotMultiplier));
	double pivotRowValues[columns];
	double pivotColumnValues[rows];
	double newRow[columns];

	for (int i = 0; i < columns; i++) {
		pivotRowValues[i] = A[pivotRow][i];
	}
	for (int i = 0; i < rows; i++) {
		pivotColumnValues[i] = A[i][pivotColumn];
	}
	for (int i = 0; i < rows; i++) {
		newRow = pivotRowValues[i] / pivotMultiplier;
	}

	B[pivotRow] /= pivotMultiplier;

	for (int i = 0; i < rows; i++){
		if (i != pivotRow) {
			for (int j = 0; j < columns; j++) {
				float multiplier = pivotColumnValues[i];
				A[i][j] -= (multiplier * newRow[j]);
			}
		}
	}
	for (int i = 0; i < B.size(); i++) {
		if (i != pivotRow) {
			float multiplier= pivotColumnValues[i];
			B[i] -= (multiplier * B[pivotRow]);
		}
	}

	float multiplier = C[pivotColumn];
	for (int i = 0; i < C.size(); i++) {
		C[i] -= (multiplier * newRow[i]);

	}

	for (int i = 0; i < columns; i++) {
		A[pivotRow][i] = newRow[i];
	}

}

void simplex::displayCurrent() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << A[i][j] << "  ";
		}
		cout << endl;
	}

	cout << endl;
}
