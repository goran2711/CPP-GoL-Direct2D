#include "HPTimer.h"

HPTimer::HPTimer()
{
	LARGE_INTEGER t;
	QueryPerformanceFrequency(&t);
	frequency = t.QuadPart;

	reset();
}


HPTimer::~HPTimer()
{
}


void HPTimer::reset()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	startTime = t.QuadPart;
	currentCallToUpdate = t.QuadPart;
	lastCallToUpdate = t.QuadPart;
}

void HPTimer::update()
{
	lastCallToUpdate = currentCallToUpdate;
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	currentCallToUpdate = t.QuadPart;
}

double HPTimer::getTimeTotal()
{
	double d = currentCallToUpdate - startTime;
	return d / frequency;
}

double HPTimer::getTimeDelta()
{
	double d = currentCallToUpdate - lastCallToUpdate;
	return d / frequency;
}