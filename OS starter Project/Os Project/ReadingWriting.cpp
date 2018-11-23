#include "stdafx.h"
#include "Os.h"
#include "ProcessStructure.h"
#include "ReadingWriting.h"


ReadingWriting::ReadingWriting(Generator* generator)
{
	this->generator = generator;
}

ReadingWriting::ReadingWriting()
{
}

bool ReadingWriting::readInput(string inputFileName)
{
	ifstream inputfile;
	inputfile.open(inputFileName);
	if (!inputfile.is_open()) 
	{ 
		cout << "failed to open file" << endl;
		return false;
	}
	//for number of process
	int Integer;
	//for the rest of the input data
	float Float;
	try
	{
		inputfile >> Integer;
		generator->setNoOfProcesses(Integer);
		inputfile >> Float;
		generator->setArrivalTimeMean(Float);
		inputfile >> Float;
		generator->setArrivalTimeStandardDeviation(Float);
		inputfile >> Float;
		generator->setBurstTimeMean(Float);
		inputfile >> Float;
		generator->setBurstTimeStandardDeviation(Float);
		inputfile >> Float;
		generator->setPriorityLamda(Float);
	}
	catch (exception e)
	{
		cout << "failed in something while reading the text file " << endl;
		inputfile.close();
		return false;
	}
	inputfile.close();

	return true;
}

bool ReadingWriting::writeOutput(string outputFileName, vector<Process>& processes)
{
	ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		cout << "failed to open file" << endl;
		return false;
	}	
	
	int n = generator->getNoOfProcesses();
	outputFile << n << endl;
	for (int i = 0; i < n ; i++)
	{
		outputFile << setprecision(2) << processes[i].processNumber << " " << processes[i].arrivalTime << "  " << processes[i].burstTime << "  " << processes[i].priority << " \n" << endl;
	}

	outputFile.close();
	return true;
}

bool ReadingWriting::readProcesses(string inputFileName,vector<Process>& processes)
{
	ifstream inputfile;
	inputfile.open(inputFileName);
	if (!inputfile.is_open())
	{
		cout << "failed to open file" << endl;
		return false;
	}
	//for number of processes
	int noOfProcesses;
	inputfile >> noOfProcesses;

	try
	{
		for (int i = 0; i < noOfProcesses; i++)
		{
			Process process;
			inputfile >> process.processNumber;
			inputfile >> process.arrivalTime;
			inputfile >> process.burstTime;
			inputfile >> process.priority;
			processes.push_back(process);
		}
	}
	catch (exception e)
	{
		cout << "failed in something while reading the text file " << endl;
		inputfile.close();
		return false;
	}
	inputfile.close();

	return true;
}

bool ReadingWriting::writeOutputArray(float time, int processNo)
{
	ofstream myfile;
	myfile.open("arr.txt", ios::app);
	if (!myfile.is_open())
	{
		cout << "file doesn;t open" << endl;
		return false;
	}
	myfile << time << " " << processNo<<endl;
	myfile.close();
	return true;

}

bool ReadingWriting::writingFinishingOutputFile()
{
	ofstream file("Statistics.txt");
	if (!file.is_open())
		return false;
	float avgTA = 0;
	float avgWTA = 0;
	Os* os = Os::getInstance();
	int size = os->getProcessses().size();
	for (int i = 0; i< size ; i++)
	{
		ProcessStructure* process = os->getProcessses()[i];
		file << "For Process " << process->process->processNumber << " :" << endl;
		file << "	Turnaround Time = " << setprecision(3) << process->getTA() << endl;
		file << "	Weighted Turnaround Time = " << setprecision(3) << process->getWTA() << endl;
		file << "	Waiting Time = " << setprecision(3) << process->getTA() - process->process->burstTime << endl << endl;;
		avgTA += process->getTA();
		avgWTA += process->getWTA();
	}
	avgTA /= size;
	avgWTA /= size;
	file << "Average Turnaround Time = " << setprecision(3) << avgTA << endl;
	file << "Average Weighted Turnaround Time = " << setprecision(3) << avgWTA << endl;
	return true;
}


ReadingWriting::~ReadingWriting()
{
}
