#pragma once
#include "stdafx.h"

#include "Process.h"
#include "Generator.h"



using namespace std;
using namespace chrono;

class ReadingWriting
{
	Generator* generator;
public:
	ReadingWriting(Generator* generator);
	ReadingWriting();
	bool readInput(string inputFileName);
	bool writeOutput(string outputFileName,vector<Process>& processes);
	bool readProcesses(string inputFileName, vector<Process>& processes);
	bool writeOutputArray(float time, int processNo);
	bool writingFinishingOutputFile();
	~ReadingWriting();
};

