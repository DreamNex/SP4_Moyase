#pragma once

#include"GameObject.h"

class Enviroment : public GameObject
{
public:
	Enviroment(Vector2 pos);
	virtual ~Enviroment() = 0;
};