// Os Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Process.h"
#include "Generator.h"
#include "ReadingWriting.h"


int main()
{

	Generator* generator = new Generator();
	ReadingWriting* readAndWrite = new ReadingWriting(generator);

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
    return 0;
}

