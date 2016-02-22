#pragma once

#include"GameObject.h"

class Tools : public GameObject
{
public:
	Tools(Vector2 pos);
	virtual ~Tools() = 0;

	void setColided(bool c) { collided = c; }
	bool getColided() { return collided; }

	virtual void reset() { collided = false; };

protected:
	bool collided;
};