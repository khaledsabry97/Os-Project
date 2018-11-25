#include "stdafx.h"
#include "FCFS.h"
#include "Os.h"

//push into the ready states
void FCFS::push(ProcessStructure * process)
{
	processes.push(process);
}

//pop it out from the ready state(finished state)
void FCFS::pop(ProcessStructure *& process)
{
	if (processes.size() != 0)
	{
	
		 processes.pop();
		 if (processes.size() == 0)
			 process == NULL;
		 else
			 process = processes.front();
	}
	else
		process = NULL;
}

FCFS::FCFS()
{
}


FCFS::~FCFS()
{
}

void FCFS::addToReadyList(ProcessStructure* process)
{
	push(process);
}

bool FCFS::schedule()
{
	if (processes.size() > 0)
	{
		process = processes.front(); // get the process in the front of the queue
		run();
		return true;
	}
	else
		return false;
		
}

void FCFS::run()
{
	//if the process is already finished from the last run then remove it and get the next one to process
	if (process->process->state == finished)
	{
		pop(process);
		if (process == NULL)
			return;
	}
	//if the process was in the ready state which mean that the process need to context switch
	if (process->process->state == ready)
	{
		readingAndWriting->writeOutputArray(timer->time, -1);//write the context switch time
		timer->time += contextSwitching;
		process->start();
	}

	//if the process was already running so keep it running 
	if (process->process->state == running)
	{
		readingAndWriting->writeOutputArray(timer->time, process->process->processNumber); //write that this time slice was the process no x was running
		timer->time += quantumTime;
		process->run(quantumTime);
	}

}