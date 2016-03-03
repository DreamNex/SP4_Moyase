#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

#include "Vector2.h"

class CollisionComponent
{
public:
	//*************************************************************************************
	//CONSTRUCTOR(S) && DESTRUCTOR
	CollisionComponent(Vector2 &origin);
	CollisionComponent();
	virtual ~CollisionComponent() = 0;

	//*************************************************************************************
	//ACCESSOR(S)
	Vector2 GetOrigin(void)const;
	Vector2* GetPointerOrigin(void)const;
	Vector2 GetCollideNormal(void)const;

	//*************************************************************************************
	//MUTATOR(S)
	void SetOrigin(Vector2& origin);
	void SetCollideNormal(Vector2 collideNormal);
protected:
	Vector2* origin;
	Vector2 collideNormal; //Normal Upon Collision
};

#endif
