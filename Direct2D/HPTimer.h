#pragma once
#include <Windows.h>

// High precision timer
class HPTimer
{
	long long startTime;
	long long lastCallToUpdate;
	long long currentCallToUpdate;
	long long frequency;
public:
	HPTimer();
	~HPTimer();

	void reset();
	void update();
	double getTimeTotal();
	double getTimeDelta();
};

