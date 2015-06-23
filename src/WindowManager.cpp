#include "WindowManager.h"
#include "InputManager.h"

using namespace std;

WindowManager::WindowManager(InputManager *inputManager)
{

	this->inputManager = inputManager;

}

WindowManager::~WindowManager()
{

	glfwTerminate();

}

bool WindowManager::init(int width, int height, std::string title, bool fullscreen)
{

	if (!glfwInit())
	{

		cout << "Failed to initialize GLFW" << endl;

		return false;

	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if(fullscreen)
		window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if(!window)
	{

		cout << "Failed to initialize GLFW Window" << endl;

		return false;

	}

	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	if(err != GLEW_OK)
	{

		cout << "Failed to initialize glew" << endl;

		return false;

	}

	return true;

}

void WindowManager::swapBuffers()
{

	glfwSwapBuffers(window);

}

bool WindowManager::processInput(bool continueGame = true)
{

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window) != 0)
		return false;

	if(glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W))
		inputManager->keyPressed(Up);

	if(glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S))
		inputManager->keyPressed(Down);

	if(glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A))
		inputManager->keyPressed(Left);

	if(glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D))
		inputManager->keyPressed(Right);

	if(glfwGetKey(window, GLFW_KEY_SPACE))
		inputManager->keyPressed(Space);

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if(mouseX != 0 && mouseY != 0)
		inputManager->mouseMoved((float) mouseX, (float) mouseY);

	glfwSetCursorPos(window, 0, 0);

	glfwPollEvents();

	return continueGame;

}