#include <iostream>
#include <cmath>
#include <vector>
#include "simplex.h"
#include <cmath>

using namespace std;

simplex::simplex(vector<vector<double>> a, vector<double> b, vector<double> c, int numVar) {
	maxZ = 0;
	columns = a[0].size();
	rows = a.size();
	numOfVariables = numVar;

	//initialize A vector
	A.resize(rows, vector<double>(columns, 0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			A[i][j] = a[i][j];
		}
	}

	//initialize B vector
	B.resize(b.size());
	for (int i = 0; i < b.size(); i++) {
		B[i] = b[i];
	}

	//initialize C vector
	C.resize(c.size());
	for (int i = 0; i < c.size(); i++) {
		C[i] = c[i];
	}
}

void simplex::runSimplexAlg() {
	bool run = isOptimum();
	cout << "Inital non optimal array: " << endl;
	displayCurrent();

	while(!run){
		bool solution = doSimplexCalc();
		if (solution) {
			break;
		}
	}
	
	cout << "Determined Optimal Array and Values: " << endl;
	displayCurrent();
	findMax();
}

bool simplex::isOptimum() {
	for (int i = 0; i < C.size(); i++) {
		if (C[i] > 0.0) {
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
	double max = -9999999;
	int index = 0;

	for (int i = 0; i < C.size(); i++) {
		if (C[i] > max) {
			max = C[i];
			index = i;
		}
	}
	return index;
}

int simplex::findSmallestB(int pivotColumn) {
	double min = 9999999;
	int index = 0;
	double *positiveValues = (double*)alloca(sizeof(double) * rows);
	vector<double> results(rows, 0);
	
	for (int i = 0; i < rows; i++){
		if (A[i][pivotColumn] > 0) {
			positiveValues[i] = A[i][pivotColumn];
		}
		else {
			positiveValues[i] = 0;
		}
	}

	for (int i = 0; i < rows; i++){
		double value = positiveValues[i];
		if (value > 0.0){
			results[i] = B[i] / value;
		}
		else {
			results[i] = 99999999;
		}
	}

	for (int i = 0; i < results.size(); i++){
		if (results[i] < min) {
			min = results[i];
			index = i;
		}
	}

	return index;
}

void simplex::doRowOperations(int pivotColumn, int pivotRow) {
	double pivotMultiplier = A[pivotRow][pivotColumn];

	maxZ -= ((C[pivotColumn] * (B[pivotRow]) / pivotMultiplier));

	double *pivotRowValues = (double *) alloca (sizeof(double)*columns);
	double *pivotColumnValues = (double*)alloca(sizeof(double) * rows);
	double *newRow = (double*)alloca(sizeof(double) * columns);

	for (int i = 0; i < columns; i++) {
		pivotRowValues[i] = A[pivotRow][i];
	}
	for (int i = 0; i < rows; i++) {
		pivotColumnValues[i] = A[i][pivotColumn];
	}
	for (int i = 0; i < columns; i++) {
		newRow[i] = pivotRowValues[i] / pivotMultiplier;
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
			float multiplier = pivotColumnValues[i];
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

void simplex::findMax() {
	cout << "Values of the constrainted variables are: " << endl;
	/*for (int i = 0; i < A.size(); i++){
		int count = 0;
		int index = 0;
		for (int j = 0; j < rows; j++){	
			if (A[j][i] == 0.0) {
				count += 1;
			}
			else if (A[j][i] == 1){
				index = j;
			}
		}

		if (count == rows - 1){
			cout << "X" << index + 1 << ": " << B[index] << endl;
		}
		else{
			cout << "X" << index + 1 << ": 0" << endl;
		}
	}
	*/
	int counter = 0;
	bool flag = false;
	vector<double> coeffB(rows);
	for (int i = 0; i < columns; i++){
		if (flag == true){
			break;
		}
		for (int j = 0; j < rows; j++) {
			if (A[j][i] == 1) {
				coeffB[counter] = B[j];
				counter += 1;
				if (counter == numOfVariables) {
					flag = true;
					break;
				}
			}
		}
	}

	coeffB.resize(counter);
	for (int i = 0; i < coeffB.size(); i++){
		cout << "X" << i + 1 << ": " << coeffB[i] << endl;
	}

	cout << endl;
	cout << "Optimized Max Value is " << fabs(maxZ) << endl;
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
