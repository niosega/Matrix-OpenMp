#include "testbench.h"
#include "timer.h"
#include <map>
#include "omp.h"
#include "matrix.h"
#include <fstream>

extern int thread; 

TestBench::TestBench(int iter, int size_strong)
{
	this->iter = iter;
	this->size_strong = size_strong;
	this->strong();
	cout << endl;
	this->weak();
	cout << endl << endl;
}

void TestBench::weak()
{
	cout << "### RUNNING BEGIN WEAK ###" << endl;
	int cores[] = {1,2,4};
	for(int j = 0; j<3; j++)
	{
		double sum_in = 0;
		
		cout << "Number of threads : "<< cores[j] << endl;
		cout << "Matrix size : " << this->size_strong*cores[j] << endl;
		omp_set_num_threads(cores[j]);
		thread = cores[j];
		for(int i = 0; i<iter; i++)
		{	
			Timer t;
			t.start();
			Matrix ma(this->size_strong*cores[j], this->size_strong*cores[j]);
			ma.init(2);

			Matrix m2 = ma;
			m2.init(4);

			Matrix m4 = ((ma*m2)*2+ma);
			unsigned long long int sum = m4.sum();
			t.stop();
			sum_in += t.time();
		}
		result_weak[cores[j]] = sum_in/iter;
	}
	cout << "### RUNNING END WEAK ###" << endl;
}

void TestBench::strong()
{
	cout << "### RUNNING BEGIN STRONG ###" << endl;
	int cores[] = {1,2,4};
	for(int j = 0; j<3; j++)
	{
		double sum_in = 0;
		
		cout << "Number of threads : "<< cores[j] << endl;
		cout << "Matrix size : " << this->size_strong << endl;
		omp_set_num_threads(cores[j]);
		thread = cores[j];
		for(int i = 0; i<iter; i++)
		{	
			Timer t;
			t.start();
			Matrix ma(this->size_strong, this->size_strong);
			ma.init(2);

			Matrix m2 = ma;
			m2.init(4);

			Matrix m4 = ((ma*m2)*2+ma);
			unsigned long long int sum = m4.sum();
			t.stop();
			sum_in += t.time();
		}
		result_strong[cores[j]] = sum_in/iter;
	}
	cout << "### RUNNING END STRONG ###" << endl;
}

void TestBench::print_result()
{
	cout << "### RESULT BEGIN STRONG ###" << endl;
	for (auto it=this->result_strong.begin(); it!=this->result_strong.end(); ++it){
		cout << "Number of cores : " << it->first << endl;
		cout << "Average time : "<< it->second << endl;
	}
	cout << "### RESULT END STRONG ###" << endl << endl;
	
	cout << "### RESULT BEGIN WEAK ###" << endl;
	for (auto it=this->result_weak.begin(); it!=this->result_weak.end(); ++it){
		cout << "Number of cores : " << it->first << endl;
		cout << "Average time : "<< it->second << endl;
	}
	cout << "### RESULT END WEAK ###" << endl;
	
}void TestBench::print_csv()
{
	ofstream myfile;
	myfile.open ("results.csv");
	myfile << "Strong\n";
	for (auto it=this->result_strong.begin(); it!=this->result_strong.end(); ++it){
		myfile << it->first << ","<< it->second << "\n";
	}
	myfile << "Weak\n";
	for (auto it=this->result_weak.begin(); it!=this->result_weak.end(); ++it){
		myfile << it->first << ","<< it->second << "\n";
	}
	
	myfile.close();
}