#ifndef _WindowManager_H
#define _WindowManager_H

#include <string>										
#include <fstream>										
#include "InputManager.h"								




class WindowManager
{
public:

	
	virtual ~WindowManager() {}

	
	virtual int Initialize(int width, int height, std::string strTitle, bool bFullScreen = false) = 0;

	
	virtual void SwapTheBuffers() = 0;

	
	virtual bool ProcessInput(bool continueGame) = 0;

	
	virtual void Destroy() = 0;

	
	virtual InputManager *GetInputManager() { return &InputManager; }

protected:

	
	InputManager InputManager;
};

#endif














