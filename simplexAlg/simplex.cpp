#include <iostream>
#include <cmath>
#include <vector>
#include "simplex.h"

using namespace std;


simplex::simplex(vector<vector<double>> a, vector<double> b, vector<double> c) {
	max = 0;

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
	bool run = false;

}

void simplex::displayCurrent() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << A[i][j] << "  ";
		}
		cout << endl;
	}

	cout << "" << endl;
}
