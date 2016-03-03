#include "RigidBody.h"
#include "CollisionHandler.h"

/*************************************************************************************************************
	CONSTRUCTOR(S) && DESTRUCTOR
*************************************************************************************************************/
RigidBody::RigidBody(CollisionComponent* cC_Compt, PhysicsComponent* pC_Compt, bool response)
{
	this->cC_Compt = cC_Compt;
	this->pC_Compt = pC_Compt;
	this->pos = (cC_Compt)->GetPointerOrigin();
	this->response = response;
	if (dynamic_cast<Circle*>(cC_Compt))
	{
		scale[0] = (dynamic_cast<Circle*>(cC_Compt))->GetRadius() * 2;
		scale[1] = (dynamic_cast<Circle*>(cC_Compt))->GetRadius() * 2;
	}
	else if (dynamic_cast<Box*>(cC_Compt))
	{
		scale[0] = (dynamic_cast<Box*>(cC_Compt))->GetWidth();
		scale[1] = (dynamic_cast<Box*>(cC_Compt))->GetHeight();
	}
}

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


/*************************************************************************************************************
	ACCESSOR(S)
*************************************************************************************************************/
float RigidBody::GetScale(int axis)const{ return this->scale[axis]; }
bool RigidBody::GetResponse(void)const{ return this->response; }
PhysicsComponent* RigidBody::GetPhysicsCompt(void)const{ return this->pC_Compt; }
CollisionComponent* RigidBody::GetCollisionCompt(void)const{ return this->cC_Compt; }


/*************************************************************************************************************
	MUTATOR(S)
*************************************************************************************************************/
void RigidBody::SetScale(float x, float y)
{
	scale[0] = x;
	scale[1] = y;
}
void RigidBody::SetResponse(bool response){ this->response = response; }
void RigidBody::SetPhysicsComponent(PhysicsComponent& pC_Compt){ this->pC_Compt = &pC_Compt; }
void RigidBody::SetCollisionComponent(CollisionComponent& cC_Compt){ this->cC_Compt = &cC_Compt; }


/*************************************************************************************************************
//COLLISION CHECK(S)
*************************************************************************************************************/
bool RigidBody::CollideWith(RigidBody *otherObject)
{
	//Temporary Variables to store which is Active/Inactive
	RigidBody *resolve;
	RigidBody *toCollide;

	//Finds Which RigidBody is Active (Affected by Physics Kinematics)
	if (this->pC_Compt->GetActive())
	{
		resolve = this;
		toCollide = otherObject;
	}
	else if (otherObject->pC_Compt->GetActive())
	{
		resolve = otherObject;
		toCollide = this;
	}
	else
		return false;

	//Check For Collision
	CollisionHandler cH;
	if (cH.CheckCollision(cC_Compt, otherObject->cC_Compt))
	{
		if (toCollide->response) //Check if Response Enabled
		{
			//Apply Collision Resolves
			CollisionResolve_PushOut(resolve, toCollide);
			CollisionResolve_Bounce(resolve, toCollide);
		}
		return true;
	}
	return false;
}


/*************************************************************************************************************
	COLLISION RESOLVE(S)
*************************************************************************************************************/
void RigidBody::CollisionResolve_Bounce(RigidBody *rb1, RigidBody *rb2)
{
	rb1->pC_Compt->toBounce(rb2->cC_Compt->GetCollideNormal());
}
void RigidBody::CollisionResolve_PushOut(RigidBody *rb1, RigidBody *rb2)
{
	CollisionHandler cH;
	cH.FindCollideNormal((Box*)rb2->cC_Compt, *rb1->pos);
	Vector2 pushOut = (rb2->GetCollisionCompt()->GetCollideNormal());
	while (cH.CheckCollision(rb1->cC_Compt, rb2->cC_Compt))
	{
		*(rb1->pos) = *(rb1->pos) + (pushOut);
	}
}


/*************************************************************************************************************
	UPDATE: Changes to Latest Variables
*************************************************************************************************************/
void RigidBody::Update(float dt)
{
	pC_Compt->Update(dt);
}
