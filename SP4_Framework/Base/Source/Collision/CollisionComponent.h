#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Vector2.h"

class CollisionComponent
{
public:
	CollisionComponent(Vector2 origin){this->origin = origin;}
	CollisionComponent();
	~CollisionComponent();


	//Accessor(s)
	Vector2 GetOrigin(void)const{ return this->origin; }

	//Mutator(s)
	void SetOrigin(Vector2 origin){ this->origin = origin; }

protected:
	Vector2 origin;
};

#endif

/*

bool collisionSphere::checkCollision(collisionSphere *target)
{
//Distance Between Their Centres
float d = pow((getCentre().x - target->getCentre().x), 2)
+ pow((getCentre().y - target->getCentre().y), 2)
+ pow((getCentre().z - target->getCentre().z), 2);

//Combined Radius of Two Bounding Spheres
float tR = pow((getRadius() + target->getRadius()), 2);

return (d <= tR);
}

bool collisionSphere::checkCollision(AABB *target)
{
float DistanceBetween = 0;
float Temp;

if (getCentre().x < target->getMinimum().x)
{
Temp = getCentre().x - target->getMinimum().x;
DistanceBetween += Temp*Temp;
}
else if (getCentre().x > target->getMaximum().x)
{
Temp = getCentre().x - target->getMaximum().x;
DistanceBetween += Temp*Temp;
}

if (getCentre().y < target->getMinimum().y)
{
Temp = getCentre().y - target->getMinimum().y;
DistanceBetween += Temp*Temp;
}
else if (getCentre().y > target->getMaximum().y)
{
Temp = getCentre().y - target->getMaximum().y;
DistanceBetween += Temp*Temp;
}

return DistanceBetween <= (getRadius() * getRadius());
}

*/