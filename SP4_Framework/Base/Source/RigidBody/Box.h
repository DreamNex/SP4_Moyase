#ifndef BOX_H
#define BOX_H

#include "CollisionComponent.h"

class Box : public CollisionComponent
{
public:
	Box(Vector2 &origin, float width, float height) : CollisionComponent(origin)
	{
		this->max = Vector2(origin.x + width / 2, origin.y + height / 2);
		this->min = Vector2(origin.x - width / 2, origin.y - height / 2);
		this->width = width;
		this->height = height;
	}
	Box();
	~Box();

	//Accessor(s)
	Vector2 GetMax(void)const{ return this->max; }
	Vector2 GetMin(void)const{ return this->min; }
	float GetWidth(void)const{ return this->width; }
	float GetHeight(void)const{ return this->height; }

	//Mutator(s)
	void SetMax(Vector2 max)
	{ 
		this->max = max;
		this->width = max.x - (*origin).x;
		this->height = max.y - (*origin).y;
	}
	void SetMin(Vector2 min)
	{
		this->min = min; 
		this->width = (*origin).x - this->min.x;
		this->height = (*origin).y - this->min.y;
	}
	void SetWidth(float width)
	{ 
		this->width = width; 
		this->max.x = (*origin).x + width;
		this->min.x = (*origin).x - width;
	}
	void SetHeight(float height)
	{
		this->height = height; 
		this->max.y = (*origin).y + height;
		this->min.y = (*origin).y - height;
	}


private:
	Vector2 max, min;
	float width, height;
};

#endif