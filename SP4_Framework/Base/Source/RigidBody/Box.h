#ifndef BOX_H
#define BOX_H

#include "CollisionComponent.h"

class Box : public CollisionComponent
{
public:
	//*************************************************************************************
	//CONSTRUCTOR(S) && DESTRUCTOR
	Box(Vector2 &origin, float width, float height);
	Box();
	~Box();

	//*************************************************************************************
	//ACCESSOR(S)
	Vector2 GetMax(void)const;
	Vector2 GetMin(void)const;
	float GetWidth(void)const;
	float GetHeight(void)const;

	//*************************************************************************************
	//MUTATOR(S)
	void SetMax(Vector2 max);
	void SetMin(Vector2 min);
	void SetWidth(float width);
	void SetHeight(float height);

private:
	Vector2 max, min;
	float width, height;
};

#endif