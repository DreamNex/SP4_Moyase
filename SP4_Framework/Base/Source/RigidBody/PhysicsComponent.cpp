#include "PhysicsComponent.h"
#include <math.h>


PhysicsComponent::PhysicsComponent()
	: v_Velocity(Vector2(0, 0))
	, v_Acceleration(Vector2(0, 0))
	, v_Force(Vector2(0, 0))
	, mass(1)
	, active(false)
	, gravity(true)
	, moving(false)
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
	float gravityForce = 9.8f;
	float co_StaticFriction = 0.55;
	float co_KineticFriction = 0.50;

	/***************************************************************************************************************************
	Horizontal Force
	****************************************************************************************************************************/
	if (v_Velocity.y == 0)
	{
		if (v_Velocity.x != 0)//Moving
		{
			//Calculate Kinetic Friction
			float kineticForce = mass * gravityForce * co_KineticFriction;

			//Check Direction of Force
			if (v_Velocity.x > 0)
				v_Force.x = v_Force.x - kineticForce;
			else if (v_Velocity.x < 0)
				v_Force.x = v_Force.x + kineticForce;

			//Update Acceleration
			v_Acceleration.x += v_Force.x / mass;

			if (v_Acceleration.x * v_Velocity.x < 0)//Negative, Not Same Direction
			{
				if (fabs(v_Acceleration.x) >= fabs(v_Velocity.x))//True = Acceleration will change Velocity Direction
				{
					//Reset to Not Moving as Friction cannot change direction.
					v_Force.x = 0;
					v_Acceleration.x = 0;
					v_Velocity.x = 0;
				}
			}
		}
		else if (v_Velocity.x == 0 && v_Force.x != 0)//Not Moving
		{
			//Calculate Budging Force to overcome for Movement
			float budgingForce = mass * gravityForce * co_StaticFriction;

			//Check if Force overcome Budging Force
			if (fabs(v_Force.x) > budgingForce)
			{
				if (v_Force.x < 0)//Check Direction of Force
					v_Force.x = v_Force.x + budgingForce;
				else
					v_Force.x = v_Force.x - budgingForce;
				v_Acceleration.x = v_Force.x / mass;
			}
		}
	}

	/***************************************************************************************************************************
	Vertical Force
	****************************************************************************************************************************/


	if (gravity)
	{
		v_Acceleration.y -= gravityForce * 0.35f;
	}

	v_Acceleration.y += v_Force.y / mass;

	//Update Velocity and Position
	v_Force.SetZero();
	v_Velocity = v_Velocity + v_Acceleration;
	*v_Pos = (*v_Pos) + v_Velocity * dt;
}