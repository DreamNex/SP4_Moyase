#include "RigidBody.h"
#include "CollisionHandler.h"

RigidBody::RigidBody()
{
	pC_Compt = new PhysicsComponent(Vector2(0, 0), 1, false, false);
	cC_Compt = new Circle(Vector2(0, 0), 1);
}


RigidBody::~RigidBody()
{
	delete pC_Compt;
	delete cC_Compt;
}

void RigidBody::CollisionResolve_Bounce(RigidBody *rb1, RigidBody *rb2)
{
	RigidBody *resolve;
	if (rb1->pC_Compt->isActive())
		resolve = rb1;
	else
		resolve = rb2;
}

void RigidBody::CollisionResolve_PushOut(RigidBody *rb1, RigidBody *rb2)
{
	/*
	RigidBody *resolve;
	if (rb1->pC_Compt->isActive())
		resolve = rb1;
	else
		resolve = rb2;

	CollisionHandler cH;
	while (cH.CheckCollision(rb1->cC_Compt, rb2->cC_Compt))
	{
	}
	*/
}

bool RigidBody::CollideWith(RigidBody *otherObject)
{
	CollisionHandler cH;
	
	return (cH.CheckCollision(cC_Compt, otherObject->cC_Compt));
}

void RigidBody::Update(float dt)
{
	pC_Compt->Update(dt);
}
