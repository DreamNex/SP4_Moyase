#include "RigidBody.h"
#include "CollisionHandler.h"

RigidBody::RigidBody()
{
	pC_Compt = new PhysicsComponent(Vector2(0, 0), 1, false);
	cC_Compt = new Circle(Vector2(0, 0), 1);
}

RigidBody::~RigidBody()
{
	delete pC_Compt;
	delete cC_Compt;
}

void RigidBody::CollisionResolve_Bounce(RigidBody *rb1, RigidBody *rb2)
{
	Vector2 temp1 = rb1->pC_Compt->GetVelocity();
	Vector2 temp = rb1->pC_Compt->GetVelocity().Normalized();

	rb1->pC_Compt->toBounce(rb2->cC_Compt->GetCollideNormal());
}

void RigidBody::CollisionResolve_PushOut(RigidBody *rb1, RigidBody *rb2)
{
	CollisionHandler cH;
	while (cH.CheckCollision(rb1->cC_Compt, rb2->cC_Compt))
	{
		*(rb1->pos) = *(rb1->pos) + (rb2->cC_Compt->GetCollideNormal());
	}
}

bool RigidBody::CollideWith(RigidBody *otherObject)
{
	CollisionHandler cH;

	RigidBody *resolve;
	RigidBody *toCollide;

	if (this->pC_Compt->GetActive())
	{
		resolve = this;
		toCollide = otherObject;
	}
	else
	{
		resolve = otherObject;
		toCollide = this;
	}


	if (cH.CheckCollision(cC_Compt, otherObject->cC_Compt))
	{
		resolve->attached = toCollide;
		if (toCollide->response)
		{
			if (dynamic_cast<Ray*>(toCollide->cC_Compt) == false)
				resolve->pC_Compt->SetGravity(false);
			if (pushout)
				CollisionResolve_PushOut(resolve, toCollide);
			if (bounce)
				CollisionResolve_Bounce(resolve, toCollide);
		}
		return true;
	}
	return false;
}

void RigidBody::Update(float dt)
{
	pC_Compt->Update(dt);
}
