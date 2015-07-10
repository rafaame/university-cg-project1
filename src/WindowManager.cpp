#include "WindowManager.h"

#include "InputManager.h"
#include "Application.h"

using namespace std;
using namespace glm;

WindowManager::WindowManager()
{



}

WindowManager::~WindowManager()
{

	glfwTerminate();

}

bool WindowManager::init(vec2 windowSize, string windowTitle, bool fullscreen)
{

	if (!glfwInit())
	{

		cout << "Failed to initialize GLFW" << endl;

		return false;

	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if(fullscreen)
		window = glfwCreateWindow(windowSize.x, windowSize.y, windowTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(windowSize.x, windowSize.y, windowTitle.c_str(), nullptr, nullptr);

	if(!window)
	{

		cout << "Failed to initialize GLFW Window" << endl;

		return false;

	}

	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, true);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
	glfwSwapInterval(0);

	glewExperimental = true;

	GLenum err = glewInit();

	if(err != GLEW_OK)
	{

		cout << "Failed to initialize glew" << endl;

		return false;

	}

	glGetError();

	return true;

}

void WindowManager::swapBuffers()
{

	glfwSwapBuffers(window);

}

bool WindowManager::processInput(bool continueGame = true)
{

	InputManager *inputManager = Application::instance()->getInputManager();

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window) != 0)
		return false;

	static bool keyState[256] = {false};

	for(uint8_t key = 1; key < 255; key++)
		if(glfwGetKey(window, key))
		{

			inputManager->keyPressed((InputCode_t ) key);

			if(!keyState[key])
			{

				inputManager->keyPressedOnce((InputCode_t) key);

				keyState[key] = true;

			}

		}
		else
		{

			if(keyState[key])
				keyState[key] = false;

		}

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if(mouseX != 0 && mouseY != 0)
		inputManager->mouseMoved(vec2(mouseX, mouseY));

	glfwSetCursorPos(window, 0, 0);

	glfwPollEvents();

	return continueGame;

}

vec2 WindowManager::getWindowSize()
{

	int width;
	int height;

	glfwGetWindowSize(window, &width, &height);

	return vec2(width, height);

}