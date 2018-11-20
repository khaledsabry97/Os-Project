#include "stdafx.h"


#include "ReadingWriting.h"


ReadingWriting::ReadingWriting(Generator* generator)
{
	this->generator = generator;
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
	for (int i = 0; i < n ; i++)
	{
		outputFile << std::setprecision(2) << processes[i].processNumber << " " << processes[i].arrivalTime << "  " << processes[i].burstTime << "  " << processes[i].priority << " \n" << endl;
	}

	outputFile.close();
	return true;
}


ReadingWriting::~ReadingWriting()
{
}
