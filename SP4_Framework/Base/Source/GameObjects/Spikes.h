#pragma once

#include "Enviroment.h"

class Spikes : public Enviroment
{
public:
	Spikes(Vector2 pos, float width, float height);
	~Spikes();

	void updateGraphics(double dt);
	void render(CSceneManager2D* SceneManager2D);

private:
	Mesh* outerMesh;

	float trans;
	bool goingup;
};