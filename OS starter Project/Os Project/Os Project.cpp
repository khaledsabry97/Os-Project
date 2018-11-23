// Os Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Process.h"
#include "Generator.h"
#include "ReadingWriting.h"
#include "Os.h"

int main()
{
	
	Generator* generator = new Generator();
	ReadingWriting* readAndWrite = new ReadingWriting(generator);
	/*
	//read input file and put its values in the generator
	readAndWrite->readInput("input.txt");

	//calculate arrivals, bursts and prioities to n numbers of processes
	vector<float> arrivals = generator->randomArrival();
	vector<float> bursts = generator->randomBurst();
	vector<int> priorities = generator->randomPriority();

	//create the processes
	vector<Process> processes = generator->generateProcesses(arrivals, bursts, priorities);
	
	//output on file the processes specification 
	readAndWrite->writeOutput("output.txt", processes);
	*/

	//these two lines should be delete it if i procduce different files
	vector<Process> processes;
	readAndWrite->readProcesses("output.txt", processes);
	//make the os
	Os* os = Os::getInstance();
	//add to the os the processes
	os->addProcesses(processes);
	//add the algo number the context switch time and the quantum slice
	os->addParameters(3, 0.25, 1);
	//run the os
	os->run();
    return 0;
}

