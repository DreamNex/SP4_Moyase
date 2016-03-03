#include "CollisionComponent.h"


/*************************************************************************************************************
	CONSTRUCTOR(S) && DESTRUCTOR
*************************************************************************************************************/
CollisionComponent::CollisionComponent(Vector2 &origin)
{ 
	this->origin = &origin; 
}

CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
	//delete origin;
}


/*************************************************************************************************************
	ACCESOR(S)
*************************************************************************************************************/
Vector2 CollisionComponent::GetOrigin(void)const{ return *origin; }
Vector2* CollisionComponent::GetPointerOrigin(void)const{ return origin; }
Vector2 CollisionComponent::GetCollideNormal(void)const{ return this->collideNormal; }


/*************************************************************************************************************
	MUTATOR(S)
*************************************************************************************************************/
void CollisionComponent::SetOrigin(Vector2& origin){ this->origin = &origin; }
void CollisionComponent::SetCollideNormal(Vector2 collideNormal){ this->collideNormal = collideNormal; }