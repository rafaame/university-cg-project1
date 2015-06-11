#ifndef _Main_H
#define _Main_H

#include "WindowManager.h"					
#include "Model.h"							
#include "TimeManager.h"					
#include "Camera.h"							
#include "InputManager.h"					


class GLApplication
{
public:

	static const int ScreenWidth = 1024;
	static const int ScreenHeight = 768;

	GLApplication() {}
	~GLApplication() { Destroy(); }

	int GLMain();

	WindowManager *GetWindowManager() { return WindowManager; }
	void SetWindowManager(WindowManager *pWindowManager) { WindowManager = pWindowManager; }

	Camera *GetCamera() { return Camera; }
	void SetCamera(Camera *pCamera) { Camera = pCamera; }

	void Initialize();

	void GameLoop();

	void Destroy();

protected:

	WindowManager *WindowManager;

	Camera *Camera;
};

#endif
