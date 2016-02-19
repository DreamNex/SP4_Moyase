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
	float gravityForce = 0.00001f;
	float co_StaticFriction = 0.6;
	float co_KineticFriction = 0.55;

	/***************************************************************************************************************************
	Horizontal Force
	****************************************************************************************************************************/
	if (v_Velocity.x == 0)//Moving
	{
		//Apply Friction
		float kineticForce = mass * gravityForce * co_KineticFriction;
		v_Force.x = v_Force.x - kineticForce;

		//Update Acceleration
		v_Acceleration.x = v_Force.x / mass;

		if (v_Acceleration.x * v_Velocity.x < 0)//Negative Value, Not Same Direction
		{
			if (v_Acceleration.x >= v_Velocity.x)//True = Acceleration will change Velocity Direction
			{
				//Reset to Not Moving as Friction cannot change direction.
				v_Force.x = 0;
				v_Acceleration.x = 0;
				v_Velocity.x = 0;
			}
		}
	}
	else if (v_Velocity.x != 0 && v_Force.x != 0)//Not Moving
	{
		//Calculate Budging Force to overcome for Movement
		float budgingForce = mass * gravityForce * co_StaticFriction;

		//Check if Force overcome Budging Force
		if (v_Force.x > budgingForce)
		{
			v_Force.x = v_Force.x - budgingForce; //Apply Opposing Force
			v_Acceleration.x = v_Force.x / mass;
		}
	}

	/***************************************************************************************************************************
	Vertical Force
	****************************************************************************************************************************/
	if (gravity)
		ApplyForce(Vector2(0, -1) * mass * gravityForce);
	v_Acceleration.y = v_Force.y / mass;
	

	//Update Velocity and Position
	v_Velocity = v_Velocity + v_Acceleration;
	*v_Pos = (*v_Pos) + v_Velocity;
}