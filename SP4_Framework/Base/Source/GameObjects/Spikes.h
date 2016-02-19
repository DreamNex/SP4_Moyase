#pragma once

#include "Enviroment.h"

class Spikes : public Enviroment
{
public:
	Spikes(Vector2 pos, float width, float height);
	~Spikes();

	void render(CSceneManager2D* SceneManager2D);

private:
	Mesh* outerMesh;
};