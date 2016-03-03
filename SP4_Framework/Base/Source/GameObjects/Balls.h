#pragma once

#include "GameObject.h"

class Balls : public GameObject
{
public:
	Balls(Vector2 pos, float diameter, const char* texturePath);
	~Balls();

	bool checkColision(GameObject *GO2);

	std::vector<Vector2> GetPath(std::vector<GameObject*>, Vector2, Vector2, float, float, float);
	void reset();
private:
	Vector2 originalPos;
	void SpecialcolisionResponce(GameObject *GO2);
};