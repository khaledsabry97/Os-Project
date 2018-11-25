#pragma once
#include "stdafx.h"
#include "Process.h"



using namespace std;
using namespace chrono;

// class is used to generate the arrival time and burst time and priority for each process and also generate range of processes
class Generator
{
	int noOfProcesses;
	float arrivalTimeMean;
	float arrivalTimeStandardDeviation;
	float burstTimeMean;
	float burstTimeStandardDeviation;
	float priorityLamda;

	/*
	get random numbers using normal distribution for processes
	arrival time, burst time
	*/

	vector<float> randomNormal(int n, float mean, float standardDeviation);

public:
	Generator();
	//setters
	void setNoOfProcesses(int n);
	void setArrivalTimeMean(float n);
	void setArrivalTimeStandardDeviation(float n);
	void setBurstTimeMean(float n);
	void setBurstTimeStandardDeviation(float n);
	void setPriorityLamda(float n);

	//getters
	int getNoOfProcesses();
	float getArrivalTimeMean();
	float getArrivalTimeStandardDeviation();
	float getBurstTimeMean();
	float getBurstTimeStandardDeviation();
	float getPriorityLamda();


	vector<float> randomArrival();
	vector<float> randomBurst();

	/*
	get random numbers using poisson for priority
	*/
	vector<int> randomPriority();


	//return processes after calculating its characterisitcs 
	vector<Process> generateProcesses(vector<float> arrivals, vector<float> bursts, vector<int> priorities);
	~Generator();
};

