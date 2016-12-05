#pragma once

#include <iostream>
#include <chrono>

using namespace std::chrono;

class Timer
{
public:

    Timer();
    void start();
    void stop();
    double time();
	
private:
    high_resolution_clock::time_point start_t;
    high_resolution_clock::time_point end_t;
};
