#include "stdafx.h"
#include "Os.h"
#include "ProcessStructure.h"
#include <iostream>

using namespace std;
Os* Os::instance = NULL;//initailize
Os::Os()
{

	timer = Timer::getInstance();
	readingAndWriting = new ReadingWriting();
	ofstream myfile;
	myfile.open("results.txt");
	myfile.clear();
	myfile.close();
}

Os *Os::getInstance()
{
	if (instance == NULL)
		instance = new Os();
	return instance;
}

vector<ProcessStructure*> Os::getProcessses()
{
	return processes;
}

void Os::hello()
{



}

void Os::addParameters(int algo, float context, float quantum)
{
	algoNo = algo; // set algo number and then select which scheduler to use
	if (algo == 1) scheduler = new HPF();
	else if (algo == 2) scheduler = new FCFS();
	else if (algo == 3) scheduler = new RR();
	else if (algo == 4) scheduler = new SRTN();
	
	scheduler->setContextSwitchQuantum(context, quantum); // set the quantum and context switch time in the scheduler
}

//to add process to the os
void Os::addProcesses(vector<Process> xprocesses)
{
	for (int i = 0; i < xprocesses.size(); i++)
	{
		ProcessStructure* pS = new ProcessStructure(xprocesses[i]);
		processes.push_back(pS);
	}
}

void Os::checkNewArrivals(bool stopped)
{
	int size = processes.size();
	vector<ProcessStructure*> procs;

	for (int i = 0; i < size; i++)
	{
		ProcessStructure* p = processes[i];
		float arrive = p->process->arrivalTime;
		float time = timer->time;
		if(arrive <= time && p->process->state == away) // if the process came in the last quantum time or at the last of it then push it into scheduler
		{
			p->pause();
			procs.push_back(p);//push it first into vector so if more than one process came then we will do some sorting before pushing it into the scheduler

		}
	}

	if (procs.size() != 0) // if nothing came don't enter
	{
		schedule(procs, stopped);
	}


}

bool Os::isAllFinished()
{
	for (int i = 0; i < processes.size(); i++)
	{
		if (processes[i]->process->state != finished)
			return false;
	}
		return true;

}

void Os::finish()
{
	readingAndWriting->writingFinishingOutputFile();
}

//sort the processes that came in the last quantum before pushing it into the scheduler
void Os::schedule(vector<ProcessStructure*> processes, bool stopped)
{
	int size = processes.size();

	if (algoNo == 1) //High Priority First
	{
		//sort according to the arrival time
		//if they are equal in the arrival time then sort according to the biggest priority
		//it they are equal also then sort according to the process number
		for (int i = 0; i< size; i++)
		{
			for (int j = i + 1; j < size && j > 0; j--)
			{
				if (processes[j]->process->arrivalTime < processes[j - 1]->process->arrivalTime)
				{
					//swap the values
					swap(processes[j], processes[j - 1]);
				}
				else if (processes[j]->process->arrivalTime == processes[j - 1]->process->arrivalTime)
				{
					if (processes[j]->process->priority > processes[j - 1]->process->priority)
						swap(processes[j], processes[j - 1]);

					else if (processes[j]->process->priority == processes[j - 1]->process->priority)
					{
						if (processes[j]->process->processNumber < processes[j - 1]->process->processNumber)
							swap(processes[j], processes[j - 1]);

					}
				}
		
				
				else
					break;
			}
		}

	}
	else if (algoNo == 2) //FCFS
	{
		//sort according to the arrival time
		//if they are equal in the arrival time then sort according to the process number
		for (int i = 0; i< size; i++)
		{
			for (int j = i + 1; j < size && j > 0; j--)
			{
				if (processes[j]->process->arrivalTime < processes[j - 1]->process->arrivalTime)
				{
					//swap the values
					swap(processes[j], processes[j - 1]);
				}
				else if (processes[j]->process->arrivalTime == processes[j - 1]->process->arrivalTime)
				{
					if (processes[j]->process->processNumber < processes[j - 1]->process->processNumber)
						swap(processes[j], processes[j - 1]);

				}

				/*
						else if (processes[j]->process->arrivalTime == processes[j - 1]->process->arrivalTime)
				{
					if (processes[j]->process->burstTime < processes[j - 1]->process->burstTime)
						swap(processes[j], processes[j - 1]);

				}
				*/
				else
					break;
			}
		}
	}
	else if (algoNo == 3) //RR
	{
		//sort according to the arrival time
		//if they are equal in the arrival time then sort according to the process number
		for (int i = 0; i< size; i++)
		{
			for (int j = i + 1; j < size && j > 0; j--)
			{
				if (processes[j]->process->arrivalTime < processes[j - 1]->process->arrivalTime)
				{
					//swap the values
					swap(processes[j], processes[j - 1]);
				}

				else if (processes[j]->process->arrivalTime == processes[j - 1]->process->arrivalTime)
				{
					if (processes[j]->process->processNumber < processes[j - 1]->process->processNumber)
						swap(processes[j], processes[j - 1]);

				}
				/*
				
				else if (processes[j]->process->arrivalTime == processes[j - 1]->process->arrivalTime)
				{
					if (processes[j]->process->priority > processes[j - 1]->process->priority)
						swap(processes[j], processes[j - 1]);

				}*/


				else
					break;
			}
		}
	}
	else if (algoNo = 4)
	{
		//sort according to the arrival time
		//if they are equal in the arrival time then sort according to the running time
		//if equals also then sort according to the process number
		for (int i = 0; i< size; i++)
		{
			for (int j = i + 1; j < size && j > 0; j--)
			{
				if (processes[j]->process->arrivalTime < processes[j - 1]->process->arrivalTime)
				{
					//swap the values
					swap(processes[j], processes[j - 1]);
				}
				else if (processes[j]->process->arrivalTime == processes[j - 1]->process->arrivalTime)
				{
					if (processes[j]->process->burstTime < processes[j - 1]->process->burstTime)
						swap(processes[j], processes[j - 1]);
					else if (processes[j]->process->burstTime == processes[j - 1]->process->burstTime)
					{
						if (processes[j]->process->processNumber < processes[j - 1]->process->processNumber)
							swap(processes[j], processes[j - 1]);
					}
				}
				else
					break;
			}
		}
	}



	for (int i = 0; i < size; i++)
		scheduler->addToReadyList(processes[i]); // add to the scheduler

	float time = timer->time;
	//if the scheduler stopped according to no process in the schdeuler so the scheduler time should start from the arrival of the first process
	if (stopped)
		timer->time += processes[0]->process->arrivalTime - time;
}


//main function that is used to run all the processes
void Os::run()
{
	bool stopped = false;
	//if there is a process not finished
	while (!isAllFinished())
	{
		//check new arrivals
		checkNewArrivals(stopped);
		//make the scheduler run
		stopped = !scheduler->schedule();
		if (stopped) // if there is no process then increment the time and write that there is no process in the last quantum time
		{
			readingAndWriting->writeOutputArray(timer->time, 0);
			timer->time += scheduler->getQuantumTime();
		}
	}
	//to write the last time that has been reach which identifies that the last process ended at this time slice
	readingAndWriting->writeOutputArray(timer->time, 0);
	//write statistics file
	finish();
}

Os::~Os()
{


}
