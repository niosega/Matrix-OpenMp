#pragma once
#include <iostream>

using namespace std;

class Matrix
{
public:

	// Contructors & destructor
    Matrix(int n, int m, int thread);
    Matrix(const Matrix& matrix);
    ~Matrix();

	// Useful methods
	void init(int val=1);
	unsigned long long int sum();
	
	// Operator Overload
	friend ostream& operator<< (ostream &out, const Matrix &matrix);
	Matrix operator+(const Matrix& matrix);
	Matrix operator*(const Matrix& matrix);
	friend Matrix operator*(const Matrix& matrix, int product);
	
private:
    int ** values;
	int n;
	int m;
	int thread;
};
