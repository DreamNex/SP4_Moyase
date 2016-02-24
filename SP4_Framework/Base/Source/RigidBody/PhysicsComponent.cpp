#include "PhysicsComponent.h"
#include <math.h>

PhysicsComponent::PhysicsComponent(Vector2 &v, float mass, bool active)
{
	v_Pos = &v;
	v_Velocity = Vector2(0, 0);
	v_Acceleration = Vector2(0, 0);
	v_Force = Vector2(0, 0);

	this->mass = mass;
	this->gravitationalForce = 10.f;
	this->co_Restitution = 0.3f;
	this->co_SE = 0.45f;
	this->co_KE = 0.35f;
	this->co_Drag = 1.1f;

	this->isActive = active;
	if (isActive)
	{
		hasGravity = true;
		hasBounce = true;
		hasFriction = true;
		hasDrag = true;
		hasPush = true;
	}
	else
	{
		hasGravity = false;
		hasBounce = false;
		hasFriction = false;
		hasDrag = false;
		hasPush = false;
	}
}

PhysicsComponent::PhysicsComponent()
	: v_Velocity(Vector2(0, 0))
	, v_Acceleration(Vector2(0, 0))
	, v_Force(Vector2(0, 0))
	, mass(1)
	, gravitationalForce(10)
	, isActive(false)
{
}

PhysicsComponent::~PhysicsComponent()
{
	//delete v_Pos;
}

void PhysicsComponent::Update(float dt)
{
	if (!isActive)
		return;

	//Temporary
	float gravityForce = 9.8f;
	float co_StaticFriction = 0.55;
	float co_KineticFriction = 0.50;

	/***************************************************************************************************************************
	Horizontal Force
	****************************************************************************************************************************/
	ApplyFriction();

	/***************************************************************************************************************************
	Vertical Force
	****************************************************************************************************************************/
	ApplyGravity();
	v_Acceleration.y += v_Force.y / mass;

	//Update Velocity and Position
	v_Force.SetZero();
	v_Velocity = v_Velocity + v_Acceleration;

	if (v_Velocity.x >= MAX_VELOCITY)
		v_Velocity.x = MAX_VELOCITY;
	if (v_Velocity.y >= MAX_VELOCITY)
		v_Velocity.y = MAX_VELOCITY;

	*v_Pos = (*v_Pos) + v_Velocity * dt;
}

void PhysicsComponent::ApplyFriction()
{
	if (v_Velocity.y == 0 && v_Acceleration.y == 0)
	{
		if (v_Velocity.x != 0)//Moving
		{
			//Calculate Kinetic Friction
			float kineticForce = mass * gravitationalForce * co_KE;

			//Check Direction of Force
			if (v_Velocity.x >= 0)
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
					this->v_Acceleration.x = 0;
					this->v_Velocity.x = 0;
					this->v_Force.x = 0;
				}
			}
		}
		else if (v_Velocity.x == 0 && v_Force.x != 0)//Not Moving
		{
			//Calculate Budging Force to overcome for Movement
			float budgingForce = mass * gravitationalForce * co_SE;

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
}

void PhysicsComponent::ApplyDrag()
{}

void PhysicsComponent::ApplyGravity()
{
	if (hasGravity)
		this->v_Acceleration.y = -gravitationalForce;
}

void PhysicsComponent::toBounce(Vector2 collideNormal)
{
	//Direction before Bounce
	Vector2 currentDirection = v_Velocity;

	//Direction after Bounce
	Vector2 bounceDirection;
	bounceDirection.componentVector(v_Velocity, collideNormal);
	bounceDirection;

	//Apply New Velocity
	v_Velocity = (currentDirection - bounceDirection * 2) * 0.5f;
	v_Acceleration.SetZero();
	v_Force.SetZero();

	if (fabs(v_Velocity.x) <= 25 && fabs(v_Velocity.y) <= 25)
	{
		v_Velocity.SetZero();
		isActive = false;
	}
	hasGravity = true;
}

void PhysicsComponent::Push(Vector2 pushForce)
{
	v_Force = v_Force + pushForce;
	this->isActive = true;
}


/*************************************************************************************************************
	ACCESOR(S)
*************************************************************************************************************/
float PhysicsComponent::GetMass(){ return this->mass; }
float PhysicsComponent::GetGravitationalForce(){ return this->gravitationalForce; }

float PhysicsComponent::GetCoRestitution(){ return this->co_Restitution; }
float PhysicsComponent::GetCoKinetic(){ return this->co_KE; }
float PhysicsComponent::GetCoStatic(){ return this->co_SE; }
float PhysicsComponent::GetCoDrag(){ return this->co_Drag; }

Vector2 PhysicsComponent::GetVelocity(){ return this->v_Velocity; }
Vector2 PhysicsComponent::GetAcceleration(){ return this->v_Acceleration; }
Vector2 PhysicsComponent::GetForce(){ return this->v_Force; }

bool PhysicsComponent::GetActive(){ return this->isActive; }
bool PhysicsComponent::GetFriction(){ return this->hasFriction; }
bool PhysicsComponent::GetDrag(){ return this->hasDrag; }
bool PhysicsComponent::GetGravity(){ return this->hasGravity; }

bool PhysicsComponent::GetBounce(){ return this->hasBounce; }
bool PhysicsComponent::GetPush(){ return this->hasPush; }



/*************************************************************************************************************
MUTATOR(S)
*************************************************************************************************************/

void PhysicsComponent::SetMass(float m){ this->mass = m; }
void PhysicsComponent::SetGravitationalForce(float gF){ this->gravitationalForce = gF; }

void PhysicsComponent::SetCoRestitution(float co){ this->co_Restitution = co; }
void PhysicsComponent::SetCoKinetic(float co){ this->co_KE = co; }
void PhysicsComponent::SetCoStatic(float co){ this->co_SE = co; }
void PhysicsComponent::SetCoDrag(float co){ this->co_Drag = co; }

void PhysicsComponent::SetVelocity(Vector2 v){ this->v_Velocity = v; }
void PhysicsComponent::SetAcceleration(Vector2 a){ this->v_Acceleration = a; }
void PhysicsComponent::SetForce(Vector2 f){ this->v_Force = f; }

void PhysicsComponent::SetActive(bool a){ this->isActive = a; }
void PhysicsComponent::SetFriction(bool f){ this->hasFriction = f; }
void PhysicsComponent::SetDrag(bool d){ this->hasDrag = d; }
void PhysicsComponent::SetGravity(bool g){ this->hasGravity = g; }

void PhysicsComponent::SetBounce(bool b){ this->hasBounce = b; }
void PhysicsComponent::SetPush(bool p){ this->hasPush = p; }
