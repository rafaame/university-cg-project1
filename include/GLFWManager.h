//***********************************************************************															 
//	
//		Julio Trasferetti Nicolucci - 8517251 
//		Rafael Silva de Milha - 8139701
//		Rafael Andreatta Martins - 7564019
//
//		Trabalho CG - Labirinto									 																	 
//***********************************************************************
#ifndef _GLFWManager_H
#define _GLFWManager_H

#include <string>										
#include <fstream>										
#include "GLFW/glfw3.h"									
#include "WindowManager.h"	
#include "InputManager.h"						

class GLFWManager : public WindowManager
{
public:

	GLFWManager()	{ }
	~GLFWManager()	{ Destroy(); }

	virtual int Initialize(int width, int height, std::string strTitle, bool bFullScreen = false) override;

	virtual void SwapTheBuffers() override;

	virtual bool ProcessInput(bool continueGame) override;

	virtual void Destroy();

protected:

	GLFWwindow* Window;
};

#endif
