#pragma once
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "Circle.h"
#include "Box.h"

class RigidBody
{
public:
	RigidBody(CollisionComponent* cC_Compt, PhysicsComponent* pC_Compt, bool response, bool bounce, bool pushout)//RigidBody(new Circle(pos, rad), new PhysicsComponent(pos, 10, enable, false))
	{
		this->cC_Compt = cC_Compt;
		this->pC_Compt = pC_Compt;
		this->bounce = bounce;
		this->pushout = pushout;
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
	RigidBody();
	~RigidBody();

	//Accesor(s)
	float GetScale(int axis){ return this->scale[axis]; }
	bool GetResponse(){ return this->response; }
	PhysicsComponent* GetPhysicsCompt(){ return this->pC_Compt; }

	//Mutator(s)
	void SetScale(float x, float y)
	{
		scale[0] = x;
		scale[1] = y;
	}
	void SetResponse(bool response){ this->response = response; }


	void CollisionResolve_Bounce(RigidBody *rb1, RigidBody *rb2);
	void CollisionResolve_PushOut(RigidBody *rb1, RigidBody *rb2);
	bool CollideWith(RigidBody *otherObject);
	void Update(float dt);

private:
	PhysicsComponent* pC_Compt;
	CollisionComponent* cC_Compt;
	Vector2 *pos;
	float scale[2];

	bool response;
	bool bounce;
	bool pushout;


	//Test for Disabling Gravity
	RigidBody* attached;
};

