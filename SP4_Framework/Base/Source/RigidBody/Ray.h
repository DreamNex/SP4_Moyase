#ifndef RAY_H
#define RAY_H

#include "CollisionComponent.h"

class Ray : public CollisionComponent
{
public:
	Ray(Vector2 &origin, Vector2 end) : CollisionComponent(origin)
	{
		this->end = end;
	}
	Ray();
	~Ray();

	//Accessor(s)
	Vector2 GetEnd(){ return this->end; }

	//Mutator(s)
	void SetEnd(Vector2 end){ this->end = end; }
private:
	Vector2 end;
};

#endif