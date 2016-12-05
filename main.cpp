#include <iostream>
#include "matrix.h"
//~ #include "timer.h"
#include <unistd.h>
#include <stdlib.h>
#include "omp.h"

using namespace std;

int thread = 1;

int main(int argc, char* argv[])
{
	if(argc != 5)
	{
		cout << "mdr" << argc << endl;
		return -1;
	}
	
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	thread = atoi(argv[3]);
	int log = atoi(argv[4]);
	omp_set_num_threads(thread);
	cout << "Number of threads : "<< thread << endl;
	Matrix ma(n, m);
	ma.init(2);
	
	Matrix m2 = ma;
	m2.init(4);
	
	Matrix m4 = ((ma*m2)*2+ma);
	unsigned long long int sum = m4.sum();
	if(log)
	{
		cout << ma;
		cout << m2;
		cout << m4;
	}
	cout << sum << endl;
	return 0;
}
