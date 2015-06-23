#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "common.h"

using namespace glm;	

class Camera;
class Player;						

enum InputCode_t
{

	kEscape = 27,
	Space = 32,
	Left = 37,
	Up = 38,
	Right = 39,
	Down = 40,
	a = 97,  A = 65,
	b = 98,  B = 66,
	c = 99,  C = 67,
	d = 100, D = 68,
	e = 101, E = 69,
	f = 102, F = 70,
	g = 103, G = 71,
	h = 104, H = 72,
	i = 105, I = 73,
	j = 106, J = 74,
	k = 107, K = 75,
	l = 108, L = 76,
	m = 109, M = 77,
	n = 110, N = 78,
	o = 111, O = 79,
	p = 112, P = 80,
	q = 113, Q = 81,
	r = 114, R = 82,
	s = 115, S = 83,
	t = 116, T = 84,
	u = 117, U = 85,
	v = 118, V = 86,
	w = 119, W = 87,
	x = 120, X = 88,
	y = 121, Y = 89,
	z = 122, Z = 90

};

class InputManager
{
public:
	
	InputManager(Camera *camera, Player *player);
	~InputManager();
	
	Camera *getCamera() { return camera; }
	Player *getPlayer() { return player; }

	void keyPressed(InputCode_t code);
	void mouseMoved(float mouseX, float mouseY);

protected:

	Camera *camera;
	Player *player;

};

#endif