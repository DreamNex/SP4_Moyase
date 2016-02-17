#pragma once
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "Box.h"
#include "Circle.h"

class RigidBody
{
public:
	RigidBody(CollisionComponent* cC_Compt, PhysicsComponent* pC_Compt)//RigidBody(new Circle(pos, rad), new PhysicsComponent(pos, 10, enable, false))
	{
		this->cC_Compt = cC_Compt;
		this->pC_Compt = pC_Compt;

		if (dynamic_cast<Circle*>(cC_Compt))
		{
			scale[0] = ((Circle&)(cC_Compt)).GetRadius();
			scale[1] = ((Circle&)(cC_Compt)).GetRadius();
		}
		else if (dynamic_cast<Box*>(cC_Compt))
		{
			scale[0] = ((Box&)(cC_Compt)).GetWidth();
			scale[1] = ((Box&)(cC_Compt)).GetHeight();
		}
	}
	RigidBody();
	~RigidBody();

	//Accesor(s)
	float GetScale(int axis)
	{
		return this->scale[axis];
	}

	//Mutator(s)
	void SetScale(float x, float y)
	{
		scale[0] = x;
		scale[1] = y;
	}


	void CollisionResolve_Bounce(RigidBody *rb1, RigidBody *rb2);
	void CollisionResolve_PushOut(RigidBody *rb1, RigidBody *rb2);
	bool CollideWith(RigidBody *otherObject);
	void Update(float dt);

private:
	PhysicsComponent* pC_Compt;
	CollisionComponent* cC_Compt;
	Vector2 *pos;
	float scale[2];
};

