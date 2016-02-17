#include "PhysicsComponent.h"


PhysicsComponent::PhysicsComponent()
:	v_Velocity(Vector2(0, 0))
,	v_Acceleration(Vector2(0,0))
,	v_Force(Vector2(0,0))
,	mass(1)
,	active(false)
,	gravity(true)
,	moving(false)
{
}

PhysicsComponent::~PhysicsComponent()
{
	
}


void PhysicsComponent::Update(float dt)
{
	if (!active)
		return;

	//Temporary
	float gravityForce = 10;
	float co_StaticFriction = 0.6;
	float co_KineticFriction = 0.55;


	float NetForce = v_Force.Length();

	if (NetForce != 0)
	{
		if (!(moving))//Standing Still
		{
			Vector2 BudgingForce = mass * gravityForce * co_StaticFriction;
			BudgingForce.y = 0;
			if (NetForce * NetForce > BudgingForce.LengthSquared())
			{
				Vector2 OpposingForce = v_Force.Normalized() * BudgingForce.Length();
				v_Force = v_Force - OpposingForce;
				moving = true;
			}
		}
		else if (moving)//Moving
		{
			//F = ma
			v_Acceleration = v_Force / this->mass;

			if (v_Velocity.IsZero() || v_Acceleration.IsZero())//????
			{
				v_Velocity.IsZero();
				v_Acceleration.IsZero();
				return;
			}

			Vector2 KineticForce = mass * gravityForce * co_KineticFriction;
			Vector2 OpposingForce = v_Velocity.Normalized() * KineticForce.Length();
			OpposingForce.y = 0;

			if (v_Force.LengthSquared() < OpposingForce.LengthSquared()) // Kinetic Force > Forward Force
			{
				if (v_Velocity.Normalized() != v_Acceleration.Normalized())//It is decelerating
				{
					if (v_Velocity.LengthSquared() < v_Acceleration.LengthSquared())//Deceleration > Velocity
					{
						v_Velocity.SetZero();
						v_Acceleration.SetZero();
						moving = false;
					}
				}
				else
					v_Force = v_Force - OpposingForce;
			}
			else
			{
				v_Velocity.SetZero();
				v_Acceleration.SetZero();
				moving = false;
			}
		}
	}

	if (gravity)
		ApplyForce(Vector2(0, -gravityForce));

	*v_Pos = (*v_Pos) + v_Velocity;
}