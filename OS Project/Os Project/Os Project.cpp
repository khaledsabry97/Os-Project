// Os Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Process.h"
#include "Generator.h"
#include "ReadingWriting.h"
#include "Os.h"

using namespace std;

void helloWorld();
string generatorFileName = "input.txt";
string ProccessesFileName = "processes.txt";
bool isGenerated = false;
float contextSwitch;
float quantumTime = 1;
int algoNo;

int main()
{
	
	Generator* generator = new Generator();
	ReadingWriting* readAndWrite = new ReadingWriting(generator);
	vector<Process> processes;

		helloWorld();
		if (isGenerated == false)
		{
			//read input file and put its values in the generator
			readAndWrite->readInput(generatorFileName);

			//calculate arrivals, bursts and prioities to n numbers of processes
			vector<float> arrivals = generator->randomArrival();
			vector<float> bursts = generator->randomBurst();
			vector<int> priorities = generator->randomPriority();

			//create the processes
			processes = generator->generateProcesses(arrivals, bursts, priorities);

			//output on file the processes specification 
			readAndWrite->writeOutput(ProccessesFileName, processes);
		}
		else
		{
			readAndWrite->readProcesses(ProccessesFileName, processes);
		}
		//make the os
		Os* os = Os::getInstance();
		//add to the os the processes
		os->addProcesses(processes);
		//add the algo number the context switch time and the quantum slice
		os->addParameters(algoNo, contextSwitch, quantumTime);
		//run the os
		os->run();
	
	
    return 0;
}

void helloWorld()
{
	quantumTime = 1;
	char defaultQuantum, defaultProcesses,defaultFileName;
	string fileName = "Processes.txt";


	cout << "					Hello to Our Scheduler Simulator" << endl<<endl;
	cout << "Do you want to generate processes ? [y/n]" << endl;
	cin >> defaultFileName;
	if (defaultFileName == 'y' || defaultFileName == 'Y')
		isGenerated = false;
	else
		isGenerated = true;
	cout << "please choose one of the algorithms :- " << endl;
	cout << "[1] HPF (Highest Priority First)" << endl;
	cout << "[2] FCFS (First Come First Serve)" << endl;
	cout << "[3] RR (Round Robin)" << endl;
	cout << "[4] STRN (Shortest Remaining Running Time)" << endl;
	cin >> algoNo;
	cout << "you choosed : ";
	switch (algoNo)
	{
	case 1:
		cout << " HPF (Highest Priority First)" << endl;
		break;
	case 2:
		cout << " FCFS (First Come First Serve) " << endl;
		break;
	case 3:
		cout << " RR (Round Robin)" << endl;
		break;
	case 4:
		cout << " STRN (Shortest Remaining Running Time)" << endl;
		break;
	default:
		break;
	}

	cout << "Enter Context Switch Time : ";
	cin >> contextSwitch;

	cout << "Do you want custom quantum time the default is 1 time unit ? [y/n]" << endl;
	cin >> defaultQuantum;
	if (defaultQuantum == 'y' || defaultQuantum == 'Y')
	{
		cout << "Enter Quantum time : ";
		cin >> quantumTime;
		cout << endl;
	}
	if (isGenerated)
	{
		cout << "The default Processes file name is ``" << ProccessesFileName << "`` Do you want to change to another file name? [y/n]" << endl;
		cin >> defaultProcesses;
		if (defaultProcesses == 'y' || defaultProcesses == 'Y')
		{
			cout << "Enter file Name (without .txt): ";
			cin >> fileName;
			fileName += ".txt";
			cout << endl;
		}
	}



}
