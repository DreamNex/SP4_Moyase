#ifndef ORBIT_H
#define ORBIT_H

#include "VectorPathing.h"

class Orbit : public VectorPathing
{
public:
	Orbit(float, float);
	Orbit();
	~Orbit();

	Vector2 GetPath(Vector2 start, Vector2 end, float speed);

private:
	float normalProportion;
	float normalLength;
};

#endif