#ifndef CIRCLE_H
#define CIRCLE_H

#include "CollisionComponent.h"

class Circle : public CollisionComponent 
{
public:
	//*************************************************************************************
	//CONSTRUCTOR(S) && DESTRUCTOR
	Circle(Vector2 &origin, float radius);
	Circle();
	~Circle();

	//*************************************************************************************
	//ACCESSOR(S)
	float GetRadius(void)const;

	//*************************************************************************************
	//MUTATOR(S)
	void SetRadius(float radius);
private:
	float radius;
};

#endif