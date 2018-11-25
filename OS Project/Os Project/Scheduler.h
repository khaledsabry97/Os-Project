#pragma once
#include "ProcessStructure.h"
#include "Timer.h"
#include "ReadingWriting.h"

//Assumption
//Context Switch happens also to the first process that come to the scheduler
class Scheduler
{
protected:
	ProcessStructure* process;//current running process
	float quantumTime; // quantum time ==> 1: is the default
	//float remainingFromTheQuantum;
	float contextSwitching;//context switching time
	Timer* timer;
	ReadingWriting* readingAndWriting;
public:
	bool stopped = false;// stopped if the scheduler is empty important for STRN

	Scheduler();

	void setContextSwitchQuantum(float contextTime, float quantum); //set quantum and context switching time
	float getQuantumTime();
	virtual void addToReadyList(ProcessStructure* process) = 0; //push to the ready list
	virtual bool schedule() = 0; //to check if the scheduler is empty or not to run the scheduler
	virtual void run() = 0; //run the scheduler


	~Scheduler();
};

