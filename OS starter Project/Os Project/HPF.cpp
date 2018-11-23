#include "stdafx.h"
#include "HPF.h"
#include "ProcessStructure.h"
#include <vector>

HPF::HPF()
{
}


HPF::~HPF()
{
}

void HPF::push(ProcessStructure * process)
{
	processes.push_back(process);
	// if the processes is less or equal to 2 in the ready state then don't enter
	//because this is a non preemptive algorithm
	if (processes.size() <= 2)
		return;

	int size = processes.size();

	//sort according to the heighest priority but don't sort the first one
	for (int i = size - 1; i > 1; i--)
	{
		if(processes[i]->process->priority > processes[i-1]->process->priority)
			swap(processes[i], processes[i - 1]);
		else if (processes[i]->process->priority == processes[i - 1]->process->priority)
		{
			if (processes[i]->process->burstTime < processes[i - 1]->process->burstTime)
				swap(processes[i], processes[i - 1]);

		}
		else
			break;
	}

}

//pop it out from the ready state(finished state)
void HPF::pop(ProcessStructure *& process)
{
	int size = processes.size();
	if (processes.size() != 0)
	{
		//this is a vector so move the process in the 0 index to the size -1 index and then remove it
		for (int i = 0; i < size-1; i++)
		{
			swap(processes[i], processes[i + 1]);
		}
		processes.pop_back();
		if (processes.size() == 0)
			process == NULL;
		else
			process = processes[0];
	}
	else
		process = NULL;
}


void HPF::addToReadyList(ProcessStructure * process)
{
	push(process);
}

bool HPF::schedule()
{
	if (processes.size() > 0)
	{
		process = processes[0]; // get the process in the front of the vector
		run();
		return true;
	}
	else
		return false;
}

void HPF::run()
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
		readingAndWriting->writeOutputArray(timer->time, -1); //write the context switch time
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

