#pragma once

#include "Enviroment.h"

class Wall : public Enviroment
{
public:
	Wall(Vector2 pos, float width, float height);
	~Wall();
};