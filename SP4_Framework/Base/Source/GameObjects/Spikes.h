#pragma once

#include "Enviroment.h"

class Spikes : public Enviroment
{
public:
	Spikes(Vector2 pos, Vector2 RespawnPos, float width, float height);
	~Spikes();

	void render(CSceneManager2D* SceneManager2D);
	Vector2 getRespawnPos(){ return respawnPos; }

private:
	Mesh* outerMesh;
	Vector2 respawnPos;
};