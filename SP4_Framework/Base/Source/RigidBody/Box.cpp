#include "Box.h"

/*************************************************************************************************************
	CONSTRUCTOR(S) && DESTRUCTOR
*************************************************************************************************************/
Box::Box(Vector2 &origin, float width, float height) : CollisionComponent(origin)
{
	this->max = Vector2(origin.x + width / 2, origin.y + height / 2);
	this->min = Vector2(origin.x - width / 2, origin.y - height / 2);
	this->width = width;
	this->height = height;
}

Box::Box():
max(Vector2(1,1)),
min(Vector2(-1,-1)),
width(2),
height(2)
{
}

Box::~Box()
{
}


/*************************************************************************************************************
	ACCESSOR(S)
*************************************************************************************************************/
Vector2 Box::GetMax(void)const{ return this->max; }
Vector2 Box::GetMin(void)const{ return this->min; }
float Box::GetWidth(void)const{ return this->width; }
float Box::GetHeight(void)const{ return this->height; }


/*************************************************************************************************************
	MUTATOR(S)
*************************************************************************************************************/
void Box::SetMax(Vector2 max)
{
	this->max = max;
	this->width = (max.x - (*origin).x) * 2;
	this->height = (max.y - (*origin).y) * 2;
	origin->x = origin->x + width / 2;
	origin->x = origin->x + height / 2;
}
void Box::SetMin(Vector2 min)
{
	this->min = min;
	this->width = ((*origin).x - this->min.x) * 2;
	this->height = ((*origin).y - this->min.y) * 2;
	origin->x = origin->x - width / 2;
	origin->x = origin->x - height / 2;
}
void Box::SetWidth(float width)
{
	this->width = width;
	this->max.x = (*origin).x + width / 2;
	this->min.x = (*origin).x - width / 2;
}
void Box::SetHeight(float height)
{
	this->height = height;
	this->max.y = (*origin).y + height / 2;
	this->min.y = (*origin).y - height / 2;
}