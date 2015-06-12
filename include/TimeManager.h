#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include "common.h"

using namespace std;

class TimeManager
{

public:
	
	static TimeManager* instance()
	{

		static TimeManager instance;
		
		return &instance;

	}

	double getDelta() { return delta; }
	double getTime();
	double getFrameRate(bool writeToConsole = false);
	
	void sleep(int milliseconds);

private:

	TimeManager();
	TimeManager(TimeManager const&);
	TimeManager& operator= (TimeManager const&);

	double delta;
	double currentTime;

};

#endif