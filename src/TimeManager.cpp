#include "TimeManager.h"	

using namespace std;													
using namespace chrono;	

TimeManager::TimeManager()
{

	delta = 0;
	currentTime = 0;

}												

double TimeManager::getFrameRate(bool writeToConsole)
{

	static double frameRate = 0.0;
	static double startTime = getTime();
	static double lastTime = getTime();
	static double currentFrameRate = 0.0;

	currentTime = getTime();
	delta = currentTime - lastTime;
	lastTime = currentTime;
	++frameRate;
	
	if(currentTime - startTime > 1.0)
	{

		startTime = currentTime;

		if(writeToConsole)
			cout << "FPS: " << (int) frameRate << endl;
		
		currentFrameRate = frameRate;
		frameRate = 0;

	}
	
	return currentFrameRate;

}



double TimeManager::getTime()
{

	auto beginningOfTime = system_clock::now().time_since_epoch();
	auto ms = duration_cast<milliseconds>(beginningOfTime).count();

	return ms * 0.001;

}

void TimeManager::sleep(int ms)
{

	this_thread::sleep_for( milliseconds(ms) );

}