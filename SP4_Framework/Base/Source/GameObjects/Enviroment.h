#pragma once

#include"GameObject.h"

class Enviroment : public GameObject
{
public:
	Enviroment(Vector2 &pos);
	virtual ~Enviroment() = 0;

	virtual void update(double dt);
	virtual void render(CSceneManager2D* SceneManager2D);
};