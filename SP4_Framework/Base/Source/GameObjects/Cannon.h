#pragma once

#include "Tools.h"

class Cannon : public Tools
{
public:
	Cannon(Vector2 &pos, float width, float height);
	~Cannon();

	void render(CSceneManager2D* SceneManager2D);
	float GetPower(void)const{ return power; }
	void SetPower(float);

	float& getAngleByReference(){ return angle; }

private:
	float angle;
	float power;
};