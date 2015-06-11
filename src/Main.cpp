//***********************************************************************															 
//	
//		Rafael Andreatta Martins - 7564019 
//                                                                       
//		Trabalho CG - Labirinto									 																	 
//***********************************************************************

#include "GL/glew.h"									
#include "Main.h"							

Model g_Model;

int GLApplication::GLMain()
{

	Initialize();
	GameLoop();
	Destroy();

	return 0;

}

void GLApplication::Initialize()
{

	if(!WindowManager || WindowManager->Initialize(ScreenWidth, ScreenHeight, "CG -  T1 - Maze", false) != 0)
		exit(-1);

	glViewport(0, 0, ScreenWidth, ScreenHeight);
	
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 
	glEnable(GL_CULL_FACE);


	// We set all vertices to position 0 and color 1 (white)
	/*Vertex3 vertices[12] = { vec3(0), vec4(1) };
	
	// Loop through 20 quads and build them from the ground to the ceiling.  The i is a float
	// so we can do division with i without having to cast every single one.  It takes 6
	// vertices to make a quad (2 triangles).  These will be lying flat instead of standing up.
	// The i/10 added or subtracted to the x and z positions gives the interesting effect of the
	// quads getting smaller as they go up and then going from smaller to larger again.
	for ( float i = 0; i < 12; i += 6 )
	{
		// The first half of the quad (triangle 1)

		// The back left vertex -- colored yellow
		vertices[0 + (int)i].xyz = vec3(-5.0f + i / 10, -5.0f + i, -5.0f + i / 10);
		vertices[0 + (int)i].rgba = vec4(1, 1, 0, 1);

		// The back right vertex -- colored red
		vertices[1 + (int)i].xyz = vec3(5.0f - i / 10, -5.0f + i, -5.0f + i / 10);
		vertices[1 + (int)i].rgba = vec4(1, 0, 0, 1);

		// The front right vertex -- colored cyan
		vertices[2 + (int)i].xyz = vec3(5.0f - i / 10, -5.0f + i, 5.0f - i / 10);
		vertices[2 + (int)i].rgba = vec4(0, 1, 1, 1);

		// The second half of the quad (triangle 2)

		// The front right vertex -- colored cyan
		vertices[3 + (int)i].xyz = vec3(5.0f - i / 10, -5.0f + i, 5.0f - i / 10);
		vertices[3 + (int)i].rgba = vec4(0, 1, 1, 1);

		// The front left vertex -- colored blue
		vertices[4 + (int)i].xyz = vec3(-5.0f + i / 10, -5.0f + i, 5.0f - i / 10);
		vertices[4 + (int)i].rgba = vec4(0, 0, 1, 1);

		// The back left vertex -- colored yellow
		vertices[5 + (int)i].xyz = vec3(-5.0f + i / 10, -5.0f + i, -5.0f + i / 10);
		vertices[5 + (int)i].rgba = vec4(1, 1, 0, 1);
	}*/

	g_Model.loadFromObj("test.obj", "Shaders/Shader.vertex", "Shaders/Shader.fragment", "uvmap.dds");

	//g_Model.Initialize(vertices, 12, "Shaders/Shader.vertex", "Shaders/Shader.fragment");
		
	Camera->SetPerspective(glm::radians(60.0f), ScreenWidth / (float)ScreenHeight, 0.01f, 1000);

	Camera->PositionCamera(0, 0, 6,	0, 0);

	g_Model.SetCamera(Camera);
	
	g_Model.SetPosition(vec3(0, 0, 0));

}

void GLApplication::GameLoop()
{

	while(WindowManager->ProcessInput(true))
	{

		TimeManager::Instance().CalculateFrameRate(true);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		g_Model.Render();

		WindowManager->SwapTheBuffers();

	}

}

void GLApplication::Destroy()
{

	g_Model.Destroy();

	if(WindowManager)
	{

		WindowManager->Destroy();

		delete WindowManager;
		WindowManager = nullptr;
		
	}
	
	if(Camera)
	{

		delete Camera;
		Camera = nullptr;

	}

}