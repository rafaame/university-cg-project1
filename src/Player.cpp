#include "Player.h"

#include "Camera.h"
#include "TimeManager.h"
#include "WindowManager.h"
#include "RenderingManager.h"
#include "PhysicsManager.h"
#include "Application.h"

#include "Light.h"

using namespace std;

Player::Player()
{

	dispVector = vec3(0, 0, 0);
	velocity = vec3(0, 0, 0);
	camera = new Camera();

	flashlight = new SpotLight();
	flashlight->position = vec3(0, 0, 0);
	flashlight->direction = vec3(0, 0, 0);
	flashlight->cutoff = 0.0f;
	flashlight->color = vec3(1, 1, 1);
	flashlight->ambientIntensity = 1;
	flashlight->diffuseIntensity = 1;
	Application::instance()->getRenderingManager()->getLightingShader()->addSpotLight(flashlight);

	capsuleController = NULL;

}

Player::~Player()
{



}

void Player::spawn(vec3 position)
{

	vec2 windowSize = Application::instance()->getWindowManager()->getWindowSize();

	camera->setPerspective(radians(60.0), windowSize.x / (float) windowSize.y, 0.01, 1000);
	camera->setPosition(position);

	capsuleController = Application::instance()->getPhysicsManager()->createCapsuleController(position);

}

void Player::toggleFlashlight()
{

	flashlight->cutoff = (flashlight->cutoff > 0) ? 0 : 20;

}

vec3 Player::getPosition()
{

	PxExtendedVec3 position = capsuleController->getPosition();

	return vec3(position.x, position.y, position.z);

}

void Player::setPosition(vec3 position)
{

	capsuleController->setPosition(PxExtendedVec3(position.x, position.y, position.z));

}

void Player::move(vec3 direction, float speed)
{

	dispVector += direction * speed * 0.3f;
	dispVector.y = 0;

}

void Player::jump()
{

	velocity.y = 4.0f;

}

void Player::simulate()
{

	double delta = TimeManager::instance()->getDelta();
	velocity.y = std::max<double>(velocity.y - 9.81f * delta, -9.81f);

	dispVector.y += velocity.y * delta;
	capsuleController->move(PxVec3(dispVector.x, dispVector.y, dispVector.z), 0.001f, delta, PxControllerFilters());
	dispVector = vec3(0, 0, 0);

	camera->setPosition(getPosition());

	flashlight->position = getPosition() + vec3(0, -1, 1);
	flashlight->direction = camera->getView();

}