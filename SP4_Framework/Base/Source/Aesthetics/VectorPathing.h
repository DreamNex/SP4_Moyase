#ifndef VECTOR_PATHING_H
#define VECTOR_PATHING_H

#include "Vector2.h"

class VectorPathing
{
	enum VECTOR_PATH
	{
		REPEL = 0,
		ATTRACT,
		ORBIT
	};
public:
	VectorPathing(int path, Vector2 start, Vector2 end);
	VectorPathing();
	~VectorPathing();

	void SetPath(int path, Vector2 start, Vector2 end);
	Vector2 GetPath();
private:
	VECTOR_PATH path;
	Vector2 end;
	Vector2 start;
};

#endif