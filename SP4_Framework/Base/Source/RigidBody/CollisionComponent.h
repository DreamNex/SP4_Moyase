#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Vector2.h"

class CollisionComponent
{
public:
	CollisionComponent(Vector2 &origin){this->origin = &origin;}
	CollisionComponent();
	virtual ~CollisionComponent() = 0;

	//Accessor(s)
	Vector2 GetOrigin(){ return *origin; }
	Vector2 GetCollideNormal(){ return this->collideNormal; }

	//Mutator(s)
	void SetCollideNormal(Vector2 collideNormal){ this->collideNormal = collideNormal; }

protected:
	Vector2* origin;
	Vector2 collideNormal;
};

#endif
