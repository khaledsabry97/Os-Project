#pragma once
#include "Process.h"
#include "Timer.h"
//this class that is essiential to part 2
// convert the process to process structure which contain more details and control on the processes
class ProcessStructure
{
	float TA; //turnaround time
	float WTA;// weight turnaround time

	Timer* timer;
	

public:
	Process * process;// process variable

	ProcessStructure(Process process);

	void start(); //running
	void pause(); //waiting
	void finish(); //finished

	void run(float quantum); // run the process for quantum time 

	//getters
	float getTA();
	float getWTA();

	~ProcessStructure();
};

