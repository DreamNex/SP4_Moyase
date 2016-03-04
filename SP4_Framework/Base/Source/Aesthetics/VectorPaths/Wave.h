#ifndef WAVE_H
#define WAVE_H

#include "VectorPathing.h"

class Wave : public VectorPathing
{
public:
	Wave(float);
	Wave();
	~Wave();

	Vector2 GetPath(Vector2 start, Vector2 end, float speed);
private:
	float normalLength;
};

#endif