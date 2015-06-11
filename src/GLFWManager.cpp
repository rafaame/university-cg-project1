#include "GL/glew.h"
#include "GLFWManager.h"
#include "Main.h"

#pragma comment(lib, "glew32s.lib")

int main()
{

	GLFWManager *pWindowManager = new GLFWManager();

	Camera *pCamera = new Camera();

	GLApplication application;
	application.SetWindowManager(pWindowManager);

	application.SetCamera(pCamera);
	pWindowManager->GetInputManager()->SetCamera(pCamera);

	return application.GLMain();

}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

int GLFWManager::Initialize(int width, int height, std::string strTitle, bool bFullScreen)
{

	glfwSetErrorCallback(error_callback);

	if ( !glfwInit() )
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	if(bFullScreen)
		Window = glfwCreateWindow(width, height, strTitle.c_str(), glfwGetPrimaryMonitor(), nullptr);
	else
		Window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr, nullptr);

	if(Window == nullptr)
	{

		fprintf(stderr, "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3\n");
		Destroy();

		return -1;

	}

	glfwMakeContextCurrent(Window);

	glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(Window, 0, 0);
	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	if(GLEW_OK != err)
	{

		fprintf(stderr, "Failed to initialize glew\n");

		return -1;

	}

	return 0;
}

void GLFWManager::SwapTheBuffers()
{

	glfwSwapBuffers(Window);

}

bool GLFWManager::ProcessInput(bool continueGame = true)
{

	if(glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(Window) != 0)
		return false;

	if(glfwGetKey(Window, GLFW_KEY_UP) || glfwGetKey(Window, GLFW_KEY_W))
		InputManager.KeyPressed(Up);

	if(glfwGetKey(Window, GLFW_KEY_DOWN) || glfwGetKey(Window, GLFW_KEY_S))
		InputManager.KeyPressed(Down);

	if(glfwGetKey(Window, GLFW_KEY_LEFT) || glfwGetKey(Window, GLFW_KEY_A))
		InputManager.KeyPressed(Left);

	if(glfwGetKey(Window, GLFW_KEY_RIGHT) || glfwGetKey(Window, GLFW_KEY_D))
		InputManager.KeyPressed(Right);

	double mouseX, mouseY;
	glfwGetCursorPos(Window, &mouseX, &mouseY);

	if(mouseX != 0 && mouseY != 0)
		InputManager.MouseMoved((float)mouseX, (float)mouseY);

	glfwSetCursorPos(Window, 0, 0);

	glfwPollEvents();

	return continueGame;

}

void GLFWManager::Destroy()
{

	glfwTerminate();

}