#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "CollisionComponent.h"
#include "Circle.h"
#include "Box.h"
#include "Ray.h"

class CollisionHandler
{
public:
	CollisionHandler();
	~CollisionHandler();

	bool FindCollideNormal(Box*, Vector2);
	bool CheckCollision(CollisionComponent*, CollisionComponent*);

	bool POINT_CIRCLE(Vector2, Circle*);
	bool POINT_BOX(Vector2, Box*);
private:
	bool CIRCLE_CIRCLE(Circle*, Circle*);
	bool CIRCLE_BOX(Circle*, Box*);
	bool CIRCLE_RAY(Circle*, Ray*);
	bool BOX_BOX(Box*, Box*);
	bool BOX_RAY(Box*, Ray*);
	bool RAY_RAY(Ray*, Ray*);
};

#endif

