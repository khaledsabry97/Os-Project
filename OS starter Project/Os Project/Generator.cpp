#include "stdafx.h"
#include "Generator.h"



vector<float> Generator::randomNormal(int n,float mean,float standardDeviation)
{
	unsigned seed = system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);

	// mean and standard deviation
	normal_distribution<double> dist(mean, standardDeviation);  

	vector<float> randomNums(n);
	for (int i = 0; i < n; i++)
		randomNums[i] = abs(float(dist(e)));
	return randomNums;
}

Generator::Generator()
{
}

void Generator::setNoOfProcesses(int n)
{
	noOfProcesses = n;
}

void Generator::setArrivalTimeMean(float n)
{
	arrivalTimeMean = n;
}

void Generator::setArrivalTimeStandardDeviation(float n)
{
	arrivalTimeStandardDeviation = n;
}

void Generator::setBurstTimeMean(float n)
{
	burstTimeMean = n;
}

void Generator::setBurstTimeStandardDeviation(float n)
{
	burstTimeStandardDeviation = n;
}

void Generator::setPriorityLamda(float n)
{
	priorityLamda = n;
}

int Generator::getNoOfProcesses()
{
	return noOfProcesses;
}

float Generator::getArrivalTimeMean()
{
	return arrivalTimeMean;
}

float Generator::getArrivalTimeStandardDeviation()
{
	return arrivalTimeStandardDeviation;
}

float Generator::getBurstTimeMean()
{
	return burstTimeMean;
}

float Generator::getBurstTimeStandardDeviation()
{
	return burstTimeStandardDeviation;
}

float Generator::getPriorityLamda()
{
	return priorityLamda;
}

//n is number of processes
vector<float> Generator::randomArrival()
{
	return randomNormal(noOfProcesses,arrivalTimeMean,arrivalTimeStandardDeviation);
}

//n is number of processes
vector<float> Generator::randomBurst()
{
	vector<float> nums = randomNormal(noOfProcesses, burstTimeMean, burstTimeStandardDeviation);
	for (int i = 0; i < nums.size(); i++)
	{
		//case could happen
		if (nums[i] == 0)
			nums[i] += 0.5;
	}
	return nums;

}


vector<int> Generator::randomPriority()
{
	unsigned seed = system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	poisson_distribution<int> dist(priorityLamda);

	vector<int> v(noOfProcesses);
	for (int i = 0; i < noOfProcesses; i++)
		v[i] = dist(e);

	return v;
}

vector<Process> Generator::generateProcesses(vector<float> arrivals, vector<float> bursts, vector<int> priorities)
{

	vector<Process> processes(noOfProcesses);
	for (int i = 0; i < noOfProcesses; i++)
	{
		processes[i].processNumber = i + 1;
		processes[i].arrivalTime = arrivals[i];
		processes[i].burstTime = bursts[i];
		processes[i].priority = priorities[i];
	}


	return processes;
}

Generator::~Generator()
{
}
