#ifndef VECTOR_PATHING_H
#define VECTOR_PATHING_H

#include "Vector2.h"

class VectorPathing
{
public:
	enum VECTOR_PATH
	{
		REPEL = 0,
		ATTRACT,
		ORBIT
	};
	VectorPathing(int path);
	VectorPathing();
	~VectorPathing();

	void SetPath(int path);
	Vector2 GetPath(Vector2 start, Vector2 end);
private:
	VECTOR_PATH path;
};

#endif