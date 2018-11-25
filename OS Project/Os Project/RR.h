#pragma once
#include "Scheduler.h"
#include <queue>

//ASSUMPTION
//if there is only one process in the ready state then don't stopped and don't make a context switch
class RR :
	public Scheduler
{
	//processes in the ready array
	queue<ProcessStructure*> processes;
	void push(ProcessStructure* process);
	void pop(ProcessStructure*& process);
	void round(ProcessStructure*& process);


public:
	RR();
	~RR();



	// Inherited via Scheduler
	virtual void addToReadyList(ProcessStructure * process) override;

	virtual bool schedule() override;

	virtual void run() override;

};

