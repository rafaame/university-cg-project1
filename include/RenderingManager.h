#ifndef RENDERINGMANAGER_H
#define RENDERINGMANAGER_H

#include "common.h"

using namespace std;
using namespace glm;
using namespace physx;

class Shader;
class LightingShader;

class ShadowMap;
class ShadowMapShader;

class Scene;

class RenderingManager
{

public:

	RenderingManager();
	~RenderingManager();

	bool init();

	LightingShader *getLightingShader() { return lightingShader; }
	Shader *getActiveShader() { return activeShader; }

	void setActiveShader(Shader *shader) { activeShader = shader; }

	void renderScene(Scene *scene);
	void renderShadowMap(Scene *scene, vec3 lightPosition, vec3 lightDirection);
	void renderModels(Scene *scene, Shader *shader = NULL);

private:

	Shader *activeShader;
	LightingShader *lightingShader;

	ShadowMap *shadowMap;
	ShadowMapShader *shadowMapShader;

};

#endif