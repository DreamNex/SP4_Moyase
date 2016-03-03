#pragma once

#include "Enviroment.h"

class Rebound : public Enviroment
{
public:
	Rebound(Vector2 pos, float radius);
	~Rebound();

	void updateGraphics(double dt);
	void render(CSceneManager2D* SceneManager2D);

	void activateWave() { waveActive = true; }

private:
	bool waveActive;
	Mesh* WaveMesh;
	float WaveScale, trans;
};