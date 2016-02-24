#pragma once

#include "Enviroment.h"

class Exit : public Enviroment
{
public:
	Exit(Vector2 pos, float width, float height);
	~Exit();
};