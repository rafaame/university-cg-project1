#ifndef SCENE_H
#define SCENE_H

#include "common.h"

using namespace std;

class Player;
class Model;
class PhysicsObject;
class PhysicsCloth;

struct PointLight;

class Scene
{

public:

	Scene();
	~Scene();

	bool init();

	void addModel(Model *model);
	void addPhysicsObject(PhysicsObject *physicsObject);
	void addPhysicsCloth(PhysicsCloth *physicsCloth);

	Player *getPlayer() { return player; }
	vector<Model *> getModels() { return models; }

	void update();
	void updatePointLight();

protected:

	Player *player;
	PointLight *pointLight;

	vector<Model *> models;
	vector<PhysicsObject *> physicsObjects;
	vector<PhysicsCloth *> physicsClothes;

};

#endif