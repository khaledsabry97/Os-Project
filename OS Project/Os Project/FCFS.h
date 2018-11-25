#pragma once
#include "Scheduler.h"
#include <queue>
class FCFS:
	public Scheduler
{
	//processes in the ready array
	queue<ProcessStructure*> processes;
	void push(ProcessStructure* process);
	void pop(ProcessStructure*& process);
public:
	FCFS();
	~FCFS();

	// Inherited via Scheduler
	//process Arrival
	virtual void addToReadyList(ProcessStructure * process) override;
	virtual bool schedule() override;
	virtual void run() override;
};

