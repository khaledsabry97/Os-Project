#include "stdafx.h"
#include "SRTN.h"

//push into the ready states
void SRTN::push(ProcessStructure * process)
{
	processes.push_back(process);
	if (!stopped) //if the scheduler stopped
		sort();
}

//pop it out from the ready state(finished state)
void SRTN::pop(ProcessStructure *& process)
{
	int size = processes.size();
	if (processes.size() != 0)
	{

		for (int i = 0; i < size - 1; i++)
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

void SRTN::sort()
{
	//if the process at the start is already finished then remove it
	if (processes[0]->process->state == finished)
	{
		Process p;
		ProcessStructure* process = new ProcessStructure(p);
		pop(process);
	}

	int size = processes.size();

	//sort according to the remaining time
	//if equals then sort according to the process number and if this includes running process then don't swap
	for (int i = 0; i< size; i++)
	{
		for (int j = i + 1; j < size && j > 0; j--)
		{
			if (processes[j]->process->remainingTime < processes[j - 1]->process->remainingTime)
			{
				if (j == 1 && processes[j-1]->process->state == running)
					processes[0]->pause();
				swap(processes[j], processes[j - 1]);
			}
			else if (processes[j]->process->remainingTime == processes[j - 1]->process->remainingTime)
			{
				if (processes[j]->process->processNumber > processes[j - 1]->process->processNumber && j != 1)
				{
					swap(processes[j], processes[j - 1]);
				}
			}
			else
				break;
		}
	}
}

SRTN::SRTN()
{
}


SRTN::~SRTN()
{
}

void SRTN::addToReadyList(ProcessStructure * process)
{
	push(process);

}

bool SRTN::schedule()
{
	if (processes.size() > 0)
	{
		process = processes[0];
		stopped = false;//means the scheduler is running
		run();
		return true;
	}
	else
	{
		stopped = true;
		return false;
	}
}

void SRTN::run()
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
		//after the quantum finishes sort so the next time you will get the shortest remaining time
		sort();
	}
}
