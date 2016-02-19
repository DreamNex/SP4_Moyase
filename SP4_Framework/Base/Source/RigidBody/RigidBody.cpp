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
	RigidBody *toCollide;
	if (rb1->pC_Compt->isActive())
	{
		resolve = rb1;
		toCollide = rb2;
	}
	else
	{
		resolve = rb2;
		toCollide = rb1;
	}

		Vector2 compt;
		compt.componentVector(resolve->pC_Compt->GetVelocity(), toCollide->cC_Compt->GetCollideNormal());
		resolve->pC_Compt->SetVelocity(resolve->pC_Compt->GetVelocity() - (compt * 2.f));
		resolve->pC_Compt->SetAcceleration(resolve->pC_Compt->GetVelocity().Normalized() * resolve->pC_Compt->GetAcceleration().Length());
}

void RigidBody::CollisionResolve_PushOut(RigidBody *rb1, RigidBody *rb2)
{
	RigidBody *resolve;
	RigidBody *toCollide;
	if (rb1->pC_Compt->isActive())
	{
		resolve = rb1;
		toCollide = rb2;
	}
	else
	{
		resolve = rb2;
		toCollide = rb1;
	}

	CollisionHandler cH;
	while (cH.CheckCollision(rb1->cC_Compt, rb2->cC_Compt))
	{
		(*resolve->pos);
		Vector2 temp1;
		Vector2 temp2;
		*(resolve->pos) = *(resolve->pos) + (toCollide->cC_Compt->GetCollideNormal());
		Vector2 temp;
	}

	//If have bounce, don't need this
	resolve->pC_Compt->SetForce(Vector2(resolve->pC_Compt->GetForce().x, 0));
	resolve->pC_Compt->SetVelocity(Vector2(resolve->pC_Compt->GetVelocity().x, 0));
	resolve->pC_Compt->SetAcceleration(Vector2(resolve->pC_Compt->GetAcceleration().x, 0));
}

bool RigidBody::CollideWith(RigidBody *otherObject)
{
	CollisionHandler cH;
	
	RigidBody *resolve;
	RigidBody *toCollide;

	if (this->pC_Compt->isActive())
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
			if (pushout)
				CollisionResolve_PushOut(this, otherObject);
			if (dynamic_cast<Ray*>(toCollide->cC_Compt) == false)
			{
				resolve->pC_Compt->SetGravity(false);
			}
		}
		return true;
	}
	return false;
}

void RigidBody::Update(float dt)
{
	pC_Compt->Update(dt);
}
