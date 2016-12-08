#pragma once

#include <map>

using namespace std;

class TestBench
{
public:

    TestBench(int iter, int size_strong);
    
    void weak();
    void strong();
    void print_result();
    void print_csv();
	
	int iter;
	
	int size_strong;
	map<int, double> result_strong;
	map<int, double> result_weak;
	
private:
    
};
