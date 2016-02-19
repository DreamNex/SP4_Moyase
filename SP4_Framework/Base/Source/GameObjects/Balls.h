#pragma once

#include "GameObject.h"

class Balls : public GameObject
{
public:
	Balls(Vector2 pos, float diameter, char*  texturePath);
	~Balls();

	bool checkColision(GameObject *GO2);

private:
	Vector2 originalPos;
	void SpecialcolisionResponce(GameObject *GO2);
};