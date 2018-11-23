#pragma once
#include "ProcessStructure.h"
#include "Timer.h"
#include "Scheduler.h"
#include "RR.h"
#include"HPF.h"
#include "FCFS.h"
#include "SRTN.h"
#include "Process.h"
#include "ReadingWriting.h"

class Os
{

	//whole processes
	vector<ProcessStructure*> processes;
	
	int algoNo; //which algorithm do i use

	Timer* timer; 
	Scheduler* scheduler; // os operates the scheduler
	static Os* instance; // singleton
	ReadingWriting* readingAndWriting; // to write files
	Os();
public:
	static Os* getInstance();
	vector<ProcessStructure*> getProcessses();

	void addParameters(int algo, float context, float quantum = 1); // add the parameters to the scheduler
	void addProcesses(vector<Process> processes); // add the processes to processStructure
	void checkNewArrivals(bool stopped); //check constantly about new processes arrivals
	bool isAllFinished(); // check if all processes states is finished
	void finish(); // print the statistics

	void schedule(vector<ProcessStructure*> processes,bool stopped); //this to sort the processes that came in the last quantum unit

	void run();

	~Os();
};

