#include "RenderingManager.h"

#include "WindowManager.h"
#include "Application.h"

#include "Light.h"
#include "ShadowMap.h"
#include "ShadowMapShader.h"

#include "Scene.h"
#include "Model.h"

using namespace std;
using namespace glm;

RenderingManager::RenderingManager()
{

	activeShader = NULL;
	lightingShader = new LightingShader();

	shadowMap = new ShadowMap();
	shadowMapShader = new ShadowMapShader();

}

RenderingManager::~RenderingManager()
{



}

bool RenderingManager::init()
{

	vec2 windowSize = Application::instance()->getWindowManager()->getWindowSize();
	glViewport(0, 0, windowSize.x, windowSize.y);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glPatchParameteri(GL_PATCH_VERTICES, 3);

	GLuint vertexArrayObjectId;
	glGenVertexArrays(1, &vertexArrayObjectId);
	glBindVertexArray(vertexArrayObjectId);

	lightingShader->init();

	//shadowMap->init(windowSize.x, windowSize.y);
	//shadowMapShader->init();

	return true;

}

void RenderingManager::renderScene(Scene *scene)
{

	//renderShadowMap(scene, light[i]->getPosition(), light[i]->getDirection());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DirectionalLight directionalLight;
 	directionalLight.color = vec3(1.0f, 1.0f, 1.0f);
    directionalLight.ambientIntensity = 1.0f;
    directionalLight.diffuseIntensity = 0.01f;
    directionalLight.direction = vec3(1.0f, 0.0, 0.0f);

 	lightingShader->setActive(true);
 	lightingShader->setDirectionalLight(directionalLight);
	lightingShader->update(scene);

	//shadowMap->bindForReading(GL_TEXTURE4);

	renderModels(scene);

	Application::instance()->getWindowManager()->swapBuffers();

}

void RenderingManager::renderShadowMap(Scene *scene, vec3 lightPosition, vec3 lightDirection)
{

	vec2 windowSize = Application::instance()->getWindowManager()->getWindowSize();

	mat4 viewMatrix = lookAt(lightPosition, lightPosition + lightDirection, vec3(0, 1, 0));
	mat4 projectionMatrix = perspective(radians(60.0f), (float) windowSize.x / windowSize.y, 0.01f, 1000.0f);
	mat4 lightViewProjectionMatrix = projectionMatrix * viewMatrix;

	shadowMap->bindForWriting();

	glClear(GL_DEPTH_BUFFER_BIT);

	shadowMapShader->setActive(true);
	shadowMapShader->setViewProjectionMatrix(lightViewProjectionMatrix);
	shadowMapShader->setTextureUnit(4);

	renderModels(scene, shadowMapShader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void RenderingManager::renderModels(Scene *scene, Shader *shader)
{

	vector<Model *> models = scene->getModels();

	for(auto it = models.begin(); it != models.end(); it++)
	{

		Model *model = (*it);
		Shader *modelShader = model->getShader();

		if(shader)
			modelShader = shader;

		if(modelShader != activeShader)
			modelShader->setActive(true);

		model->render();

	}

}