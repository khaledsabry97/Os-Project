#pragma once
class Timer
{
	static Timer* instance; // singleton that calculate the time for the whole run
	Timer();
public:
	float time; //for simplicity i put it at global 
	static Timer* getInstance();

	
	~Timer();
};

