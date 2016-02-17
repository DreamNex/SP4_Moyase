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

	bool CheckCollision(CollisionComponent*, CollisionComponent*);
private:
	bool CIRCLE_CIRCLE(Circle&, Circle&);
	bool CIRCLE_BOX(Circle&, Box&);
	bool CIRCLE_RAY(Circle&, Ray&);
	bool BOX_BOX(Box&, Box&);
	bool BOX_RAY(Box&, Ray&);
	bool RAY_RAY(Ray&, Ray&);
};

#endif

