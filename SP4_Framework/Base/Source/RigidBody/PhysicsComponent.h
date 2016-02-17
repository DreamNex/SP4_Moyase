#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Vector2.h"

class PhysicsComponent
{
public:
	PhysicsComponent(Vector2 &v, float mass, bool gravity, bool active)
	{
		v_Pos = &v;
		v_Velocity = Vector2(0, 0);
		v_Acceleration = Vector2(0, 0);
		v_Force = Vector2(0, 0);

		this->mass = mass;
		this->active = active;
		this->gravity = gravity;
		this->moving = false;
	}
	PhysicsComponent();
	~PhysicsComponent();

	//Accessor(s)
	Vector2 GetVelocity(){ return this->v_Velocity; }
	Vector2 GetAcceleration(){ return this->v_Acceleration; }
	Vector2 GetForce(){ return this->v_Force; }
	float GetMass(){ return this->mass; }
	bool isActive(){ return this->active; }
	bool hasGravity(){ return this->gravity; }

	//Mutator(s)
	void SetVelocity(Vector2 v){ this->v_Velocity = v; }
	void SetAcceleration(Vector2 a){ this->v_Acceleration = a; }
	void SetForce(Vector2 f){ this->v_Force = f; }
	void SetMass(float m){ this->mass = m; }
	void SetActive(bool active){ this->active = active; }
	void SetGravity(bool gravity){ this->gravity = gravity; }

	void ApplyForce(Vector2 appliedForce){ v_Force = v_Force + appliedForce; }
	void Update(float dt);

private:
	float mass;
	Vector2* v_Pos;
	Vector2 v_Velocity;
	Vector2 v_Acceleration;
	Vector2 v_Force;

	bool active;
	bool gravity;
	bool moving;
};

#endif