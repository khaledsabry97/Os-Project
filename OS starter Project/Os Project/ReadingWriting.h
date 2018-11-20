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

	bool readInput(string inputFileName);
	bool writeOutput(string outputFileName,vector<Process>& processes);
	~ReadingWriting();
};

