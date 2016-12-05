#include "timer.h"
#include <chrono>
#include <ctime>
#include <ratio>

using namespace std::chrono;

Timer::Timer()
{
	
}

void Timer::start()
{
	this->start_t = high_resolution_clock::now();
}

void Timer::stop()
{
	this->end_t = high_resolution_clock::now();
}

double Timer::time()
{
	return duration_cast<duration<double>>(this->end_t - this->start_t).count();
}
