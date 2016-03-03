#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "CollisionComponent.h"
#include "Circle.h"
#include "Box.h"
#include "Ray.h"

class CollisionHandler
{
public:
	//*************************************************************************************
	//CONSTRUCTOR(S) && DESTRUCTOR
	CollisionHandler();
	~CollisionHandler();

	//*************************************************************************************
	//COLLISION CHECKS
	bool CheckCollision(CollisionComponent*, CollisionComponent*);

	bool POINT_CIRCLE(Vector2, Circle*);
	bool POINT_BOX(Vector2, Box*);

	bool CIRCLE_CIRCLE(Circle*, Circle*);
	bool CIRCLE_BOX(Circle*, Box*);

	bool BOX_BOX(Box*, Box*);

	//*************************************************************************************
	//AFTER-COLLISION EFFECT : Change Variables after Collision
	bool FindCollideNormal(Box*, Vector2);
};

#endif

