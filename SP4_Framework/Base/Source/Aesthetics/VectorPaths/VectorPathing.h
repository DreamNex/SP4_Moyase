#ifndef VECTOR_PATHING_H
#define VECTOR_PATHING_H

#include "Vector2.h"
#include <math.h>

class VectorPathing
{
public:
	VectorPathing();
	~VectorPathing();

	virtual Vector2 GetPath(Vector2 start, Vector2 end, float speed) = 0;
};

#endif