#include "stdafx.h"
#include "Timer.h"

Timer* Timer::instance = NULL;

Timer::Timer()
{
	time = 0;
}


Timer* Timer::getInstance()
{
	if (instance == NULL)
	{
		instance = new Timer();
	}

	return instance;
}


Timer::~Timer()
{
}
