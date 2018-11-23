#pragma once


#include "stdafx.h"
#include "States.h"
struct Process 
{
	int processNumber =0;
	float arrivalTime =0;
	float burstTime = 0;
	int priority = 0;
	float remainingTime = 0;
	float endTime = 0; //finishing time
	State state = away;
};
