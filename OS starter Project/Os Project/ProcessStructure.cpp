#include "stdafx.h"
#include "ProcessStructure.h"
#include "States.h"

ProcessStructure::ProcessStructure(Process cProcess)
{
	process = new Process();
	process->processNumber = cProcess.processNumber;
	process->arrivalTime = cProcess.arrivalTime;
	process->burstTime = cProcess.burstTime;
	process->remainingTime = cProcess.burstTime;
	process->priority = cProcess.priority;
	process->endTime = 0;
	process->state = away;
	TA = 0;
	WTA = 0;
	timer = Timer::getInstance();
}



void ProcessStructure::run(float quantum)
{
	//if the remainingtime is 0.5 and the quantum is 2 then you will stop the process before end of quantum
	process->remainingTime -= quantum;
	float remainingTime = process->remainingTime;
	if (remainingTime <= 0) //if the remainging time is less than or equal 0 then make it zero and state = finish
	{
		//add this portion to the time
		timer->time = timer->time + remainingTime; //so the processor stop at the correct time of finishing the process
		process->remainingTime = 0;
		finish();
	}
}

void ProcessStructure::start()
{
	process->state = running;
}

void ProcessStructure::pause()
{
	process->state = ready;
}

void ProcessStructure::finish()
{
	process->endTime = timer->time;
	TA = process->endTime - process->arrivalTime; //turnaround = final - arrival
	WTA = TA / process->burstTime; 
	process->state = finished;
}

float ProcessStructure::getTA()
{
	return TA;
}

float ProcessStructure::getWTA()
{
	return WTA;
}

ProcessStructure::~ProcessStructure()
{
}
