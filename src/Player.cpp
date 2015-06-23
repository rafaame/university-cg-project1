#include "Player.h"
#include "Camera.h"
#include "Application.h"
#include "TimeManager.h"
#include "PhysicsManager.h"

Player::Player(Camera *camera)
{

	dispVector = vec3(0, 0, 0);
	velocity = vec3(0, 0, 0);

	this->camera = camera;
	capsuleController = NULL;

}

Player::~Player()
{



}

void Player::spawn(vec3 position)
{

	capsuleController = gApplication->getPhysicsManager()->createCapsuleController(position);

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

void Player::move(double speed)
{

	vec3 viewVector = camera->getView();
	dispVector += viewVector * (float) speed * 0.1f;
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

	cout << "Velocity: " << velocity.x << " " << velocity.y << " " << velocity.z << endl;

	dispVector.y += velocity.y * delta;
	capsuleController->move(PxVec3(dispVector.x, dispVector.y, dispVector.z), 0.001f, delta, PxControllerFilters());
	dispVector = vec3(0, 0, 0);

	vec3 position = getPosition();
	camera->setPosition(position);

}