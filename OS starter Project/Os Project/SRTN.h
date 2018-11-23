#pragma once
#include "Scheduler.h"
class SRTN :
	public Scheduler
{	//processes in the ready array
	vector<ProcessStructure*> processes;
	void push(ProcessStructure* process);
	void pop(ProcessStructure*& process);
	void sort();
public:
	SRTN();
	~SRTN();

	// Inherited via Scheduler
	virtual void addToReadyList(ProcessStructure * process) override;
	virtual bool schedule() override;
	virtual void run() override;
};

