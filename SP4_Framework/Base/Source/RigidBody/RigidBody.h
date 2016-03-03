#pragma once
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "Circle.h"
#include "Box.h"

class RigidBody
{
public:
	//*************************************************************************************
	//CONSTRUCTOR(S) && DESTRUCTOR
	RigidBody(CollisionComponent* cC_Compt, PhysicsComponent* pC_Compt, bool response);
	RigidBody();
	~RigidBody();

	//*************************************************************************************
	//ACCESSOR(S)
	float GetScale(int axis)const;
	bool GetResponse(void)const;
	PhysicsComponent* GetPhysicsCompt(void)const;
	CollisionComponent* GetCollisionCompt(void)const;

	//*************************************************************************************
	//MUTATOR(S)
	void SetScale(float x, float y);
	void SetResponse(bool response);
	void SetPhysicsComponent(PhysicsComponent& pC_Compt);
	void SetCollisionComponent(CollisionComponent& cC_Compt);

	//*************************************************************************************
	//COLLISION CHECK(S)
	bool CollideWith(RigidBody *otherObject);

	//*************************************************************************************
	//UPDATE: Changes to Latest Variables
	void Update(float dt);

private:
	//Collision Resolves
	void CollisionResolve_Bounce(RigidBody *rb1, RigidBody *rb2);
	void CollisionResolve_PushOut(RigidBody *rb1, RigidBody *rb2);

	bool response; //Enable Resolve
	bool bounce; //Enable Bounce
	bool pushout; //Enable Pushout

	//Components
	PhysicsComponent* pC_Compt;
	CollisionComponent* cC_Compt;

	Vector2 *pos;
	float scale[2]; //Scale of Body (For Rendering)
};

