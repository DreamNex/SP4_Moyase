#include "CollisionHandler.h"
#include <math.h>
#include "Vector3.h"

#define PI

CollisionHandler::CollisionHandler()
{
}


CollisionHandler::~CollisionHandler()
{
}



bool CollisionHandler::CheckCollision(CollisionComponent* c1, CollisionComponent* c2)
{
	if (dynamic_cast<Circle*>(c1))//Checks if c1 is a Circle
	{
		if (dynamic_cast<Circle*>(c2))
			return CIRCLE_CIRCLE((Circle*)c1, (Circle*)c2);
		if (dynamic_cast<Box*>(c2))
			return CIRCLE_BOX((Circle*)c1, (Box*)c2);
		if (dynamic_cast<Ray*>(c2))
			return CIRCLE_RAY((Circle*)c1, (Ray*)c2);
	}
	else if (dynamic_cast<Box*>(c1))//Checks if c1 is a Box
	{
		if (dynamic_cast<Circle*>(c2))
			return CIRCLE_BOX((Circle*)c2, (Box*)c1);
		if (dynamic_cast<Box*>(c2))
			return BOX_BOX((Box*)c1, (Box*)c2);
		if (dynamic_cast<Ray*>(c2))
			return BOX_RAY((Box*)c1, (Ray*)c2);
	}
	else if (dynamic_cast<Ray*>(c1))//Checks if c1 is a ray
	{
		if (dynamic_cast<Circle*>(c2))
			return CIRCLE_RAY((Circle*)c2, (Ray*)c1);
		if (dynamic_cast<Box*>(c2))
			return BOX_RAY((Box*)c2, (Ray*)c1);
		if (dynamic_cast<Ray*>(c2))
			return RAY_RAY((Ray*)c1, (Ray*)c2);
	}
	return false;
}


bool CollisionHandler::POINT_CIRCLE(Vector2 v1, Circle* c1)
{
	//Total Radius of the Circles
	float totalRadius = c1->GetRadius();

	//Length In Between
	float xDiff = c1->GetOrigin().x - v1.x;
	float yDiff = c1->GetOrigin().y - v1.y;
	float lengthBetween = (xDiff * xDiff) + (yDiff * yDiff);

	//True if Total Radius^2 >= Length Between
	if ((totalRadius * totalRadius) >= lengthBetween)
	{
		c1->SetCollideNormal((Vector2(xDiff, yDiff)).Normalized());
	}
	return false;
}
bool CollisionHandler::POINT_BOX(Vector2 v1, Box* b1)
{
	Vector2 max = b1->GetOrigin() + Vector2(b1->GetWidth() / 2, b1->GetHeight() / 2);
	Vector2 min = b1->GetOrigin() - Vector2(b1->GetWidth() / 2, b1->GetHeight() / 2);
	if (v1.x <= max.x && v1.x >= min.x)//Within X Range of Box
	{
		if (v1.y <= max.y && v1.x >= min.y)//Within Y Range of Box
			return true;
	}
	return false;
}

bool CollisionHandler::CIRCLE_CIRCLE(Circle* c1, Circle* c2)
{
	//Total Radius of the Circles
	float totalRadius = c1->GetRadius() + c2->GetRadius();
	
	//Length In Between
	float xDiff = c1->GetOrigin().x - c2->GetOrigin().x;
	float yDiff = c1->GetOrigin().y - c2->GetOrigin().y;
	float lengthBetween = (xDiff * xDiff) + (yDiff * yDiff);

	//True if Total Radius^2 >= Length Between
	if ((totalRadius * totalRadius) >= lengthBetween)
	{
		c1->SetCollideNormal( (c2->GetOrigin() - c1->GetOrigin()).Normalized() );
		c2->SetCollideNormal((c1->GetOrigin() - c2->GetOrigin()).Normalized());
		return true;
	}
	return false;
}
bool CollisionHandler::CIRCLE_BOX(Circle* c1, Box* b1)
{
	float DistanceBetween = 0;
	float Temp;
	Vector2 max = b1->GetOrigin() + Vector2(b1->GetWidth() / 2, b1->GetHeight() / 2);
	Vector2 min = b1->GetOrigin() - Vector2(b1->GetWidth() / 2, b1->GetHeight() / 2);

	if (c1->GetOrigin().x < min.x) //Left
	{
		Temp = c1->GetOrigin().x - min.x;
		DistanceBetween += Temp*Temp;
	}
	else if (c1->GetOrigin().x > max.x) //Right
	{
		Temp = c1->GetOrigin().x - max.x;
		DistanceBetween += Temp*Temp;
	}
	if (c1->GetOrigin().y < min.y) // Down
	{
		Temp = c1->GetOrigin().y - min.y;
		DistanceBetween += Temp*Temp;
	}
	else if (c1->GetOrigin().y > max.y) // Up
	{
		Temp = c1->GetOrigin().y - max.y;
		DistanceBetween += Temp*Temp;
	}
	
	//Check for Collision
	if ((DistanceBetween <= (c1->GetRadius() * c1->GetRadius())))
	{
		return true;
	}
	return false;
}
bool CollisionHandler::CIRCLE_RAY(Circle*, Ray*)
{

	return false;
}
bool CollisionHandler::BOX_BOX(Box* b1, Box* b2)
{
	return (b1->GetOrigin().x > b2->GetMin().x && b1->GetOrigin().x < b2->GetMax().x &&
			b1->GetOrigin().y > b2->GetMin().y && b1->GetOrigin().y < b2->GetMax().x);
}
bool CollisionHandler::BOX_RAY(Box*, Ray*)
{
	return false;
}
bool CollisionHandler::RAY_RAY(Ray*, Ray*)
{
	return false;
}


bool CollisionHandler::FindCollideNormal(Box* b1, Vector2 origin)
{
	Vector2 up(0, 1);
	Vector2 down(0, -1);
	Vector2 right(1, 0);
	Vector2 left(-1, 0);
	if ((origin - b1->GetOrigin()).IsZero())
	{
		b1->SetCollideNormal(Vector2(0, 1));
		return true;
	}
	Vector2 dir = (origin - b1->GetOrigin()).Normalized();
	Vector2 max = b1->GetOrigin() + Vector2(b1->GetWidth()/2, b1->GetHeight()/2);

	if ((max - b1->GetOrigin()).IsZero())
	{
		b1->SetCollideNormal(Vector2(0, 1));
		return true;
	}
	float horizontalDotLimit = right.Dot((max - b1->GetOrigin()).Normalized());
	float verticalDotLimit = up.Dot((max - b1->GetOrigin()).Normalized());

	if (up.Dot(dir) > verticalDotLimit && up.Dot(dir) < 1)//Up
		b1->SetCollideNormal(up);
	else if (down.Dot(dir) > verticalDotLimit && down.Dot(dir) < 1)//Down
		b1->SetCollideNormal(down);
	else if (right.Dot(dir) > horizontalDotLimit && right.Dot(dir) < 1)//Right
		b1->SetCollideNormal(right);
	else if (left.Dot(dir) > horizontalDotLimit && left.Dot(dir) < 1)//Left
		b1->SetCollideNormal(left);
	else //Corner
		b1->SetCollideNormal((dir.unary()));

	return true;
}