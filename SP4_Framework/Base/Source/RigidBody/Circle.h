#ifndef CIRCLE_H
#define CIRCLE_H

#include "CollisionComponent.h"

class Circle : public CollisionComponent 
{
public:
	Circle(Vector2 &origin, float radius) : CollisionComponent(origin)
	{
		this->radius = radius;
	}
	Circle();
	~Circle();

	//Accessor(s)
	float GetRadius(void)const{ return this->radius; }

	//Mutator(s)
	void SetRadius(float radius){ this->radius = radius; }
private:
	float radius;
};

#endif