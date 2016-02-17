#include "CollisionHandler.h"

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
			return CIRCLE_CIRCLE((Circle&)c1, (Circle&)c2);
		if (dynamic_cast<Box*>(c2))
			return CIRCLE_BOX((Circle&)c1, (Box&)c2);
		if (dynamic_cast<Ray*>(c2))
			return CIRCLE_RAY((Circle&)c1, (Ray&)c2);
	}
	else if (dynamic_cast<Box*>(c1))//Checks if c1 is a Box
	{
		if (dynamic_cast<Circle*>(c2))
			return CIRCLE_BOX((Circle&)c2, (Box&)c1);
		if (dynamic_cast<Box*>(c2))
			return BOX_BOX((Box&)c1, (Box&)c2);
		if (dynamic_cast<Ray*>(c2))
			return BOX_RAY((Box&)c1, (Ray&)c2);
	}
	else if (dynamic_cast<Ray*>(c1))//Checks if c1 is a ray
	{
		if (dynamic_cast<Circle*>(c2))
			return CIRCLE_RAY((Circle&)c2, (Ray&)c1);
		if (dynamic_cast<Box*>(c2))
			return BOX_RAY((Box&)c2, (Ray&)c1);
		if (dynamic_cast<Ray*>(c2))
			return RAY_RAY((Ray&)c1, (Ray&)c2);
	}
	return false;
}

bool CollisionHandler::CIRCLE_CIRCLE(Circle& c1, Circle& c2)
{
	//Total Radius of the Circles
	float totalRadius = c1.GetRadius() + c2.GetRadius();
	
	//Length In Between
	float xDiff = c1.GetOrigin().x - c2.GetOrigin().x;
	float yDiff = c1.GetOrigin().y - c2.GetOrigin().y;
	float lengthBetween = (xDiff * xDiff) + (yDiff * yDiff);

	//True if Total Radius^2 >= Length Between
	if ((totalRadius * totalRadius) >= lengthBetween)
	{
		c1.SetCollideNormal( (c2.GetOrigin() - c1.GetOrigin()).Normalized() );
		c2.SetCollideNormal((c1.GetOrigin() - c2.GetOrigin()).Normalized());
	}
	return false;
}
bool CollisionHandler::CIRCLE_BOX(Circle& c1, Box& b1)
{
	float DistanceBetween = 0;
	float Temp;

	if (c1.GetOrigin().x < b1.GetMin().x)
	{
		Temp = c1.GetOrigin().x - b1.GetMin().x;
		DistanceBetween += Temp*Temp;
	}
	else if (c1.GetOrigin().x > b1.GetMax().x)
	{
		Temp = c1.GetOrigin().x - b1.GetMax().x;
		DistanceBetween += Temp*Temp;
	}

	if (c1.GetOrigin().y < b1.GetMin().y)
	{
		Temp = c1.GetOrigin().y - b1.GetMin().y;
		DistanceBetween += Temp*Temp;
	}
	else if (c1.GetOrigin().y > b1.GetMax().y)
	{
		Temp = c1.GetOrigin().y - b1.GetMax().y;
		DistanceBetween += Temp*Temp;
	}

	return DistanceBetween <= ( c1.GetRadius() * c1.GetRadius() );
}
bool CollisionHandler::CIRCLE_RAY(Circle&, Ray&)
{

	return false;
}
bool CollisionHandler::BOX_BOX(Box& b1, Box& b2)
{
	return (b1.GetOrigin().x > b2.GetMin().x && b1.GetOrigin().x < b2.GetMax().x &&
			b1.GetOrigin().y > b2.GetMin().y && b1.GetOrigin().y < b2.GetMax().x);
}
bool CollisionHandler::BOX_RAY(Box&, Ray&)
{
	return false;
}
bool CollisionHandler::RAY_RAY(Ray&, Ray&)
{
	return false;
}