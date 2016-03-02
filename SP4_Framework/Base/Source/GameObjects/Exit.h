#pragma once

#include "Enviroment.h"

class Exito : public Enviroment
{
public:
	Exito(Vector2 pos, float width, float height);
	~Exito();

	void updateGraphics(double dt);
	void render(CSceneManager2D* SceneManager2D);

private:
	float trans;
	bool goingup;
};