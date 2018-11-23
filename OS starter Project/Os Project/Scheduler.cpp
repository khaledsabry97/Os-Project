#include "stdafx.h"
#include "Scheduler.h"


Scheduler::Scheduler()
{
	timer = Timer::getInstance();
	process = NULL;
	readingAndWriting = new ReadingWriting();
}

void Scheduler::setContextSwitchQuantum(float contextTime, float quantum)
{
	quantumTime = quantum;
//	remainingFromTheQuantum = quantumTime;
	contextSwitching = contextTime;
}

float Scheduler::getQuantumTime()
{
	return quantumTime;
}


Scheduler::~Scheduler()
{
}
