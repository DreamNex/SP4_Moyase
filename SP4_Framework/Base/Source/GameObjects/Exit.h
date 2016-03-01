#pragma once

#include "Enviroment.h"

class Exit : public Enviroment
{
public:
	Exit(Vector2 pos, float width, float height);
	~Exit();

	void updateGraphics(double dt);
	void render(CSceneManager2D* SceneManager2D);

private:
	float trans;
	bool goingup;
};