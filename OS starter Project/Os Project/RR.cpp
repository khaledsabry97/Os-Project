#include "stdafx.h"
#include "RR.h"

//push into the ready states
void RR::push(ProcessStructure * process)
{
	processes.push(process);
}

//pop it out from the ready state(finished state)
void RR::pop(ProcessStructure *& process)
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

//round every quantum time
void RR::round(ProcessStructure *& process)
{
	if (processes.size() > 1)
	{
		ProcessStructure* proc = processes.front();
		processes.pop(); //pop it
		proc->pause();
		processes.push(proc); // then push it again in the back
		if (processes.size() == 0)
			process == NULL;
		else
			process = processes.front();//get the fron process
	}
}

RR::RR()
{
}


RR::~RR()
{
}

void RR::addToReadyList(ProcessStructure * process)
{
	push(process);
}

bool RR::schedule()
{

	if (processes.size() > 0)
	{
		process = processes.front();
		run();
		return true;
	}
	else
		return false;
}

void RR::run()
{
	//this is running from last turn then round the process and return the next process
	if (process->process->state == running)
	{
		round(process);
	}

	//if the process is already finished from the last run then remove it and get the next one to process
	if (process->process->state == finished)
	{
		pop(process); //remove it
		if (process == NULL)
			return;
	}

	//if the process was in the ready state which mean that the process need to context switch
	if (process->process->state == ready)
	{
		readingAndWriting->writeOutputArray(timer->time, -1);
		timer->time += contextSwitching;
		process->start();
	}

	//if the process was already running so keep it running 
	if (process->process->state == running)
	{
		readingAndWriting->writeOutputArray(timer->time, process->process->processNumber);
		timer->time += quantumTime;
		process->run(quantumTime);
	}
}

