#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Vector2.h"

//By the Legendary Quen

class PhysicsComponent
{
public:
	PhysicsComponent(Vector2 &v, float mass, bool active);
	PhysicsComponent();
	~PhysicsComponent();

	//*************************************************************************************
	//ACCESSOR(S)
	float GetMass();
	float GetGravitationalForce();

	float GetCoRestitution();
	float GetCoKinetic();
	float GetCoStatic();
	float GetCoDrag();

	Vector2 GetVelocity();
	Vector2 GetAcceleration();
	Vector2 GetForce();

	bool GetActive();
	bool GetFriction();
	bool GetDrag();
	bool GetGravity();

	bool GetBounce();
	bool GetPush();

	//*************************************************************************************
	//MUTATOR(S)
	void SetMass(float);
	void SetGravitationalForce(float);

	void SetCoRestitution(float);
	void SetCoKinetic(float);
	void SetCoStatic(float);
	void SetCoDrag(float);

	void SetVelocity(Vector2);
	void SetAcceleration(Vector2);
	void SetForce(Vector2);

	void SetActive(bool);
	void SetFriction(bool);
	void SetDrag(bool);
	void SetGravity(bool);

	void SetBounce(bool);
	void SetPush(bool);

	//Manual Apply Functions: Changes the Vector2/Kinematics
	void Push(Vector2);
	void toBounce(Vector2);
	void Update(float dt);

private:

	//Auto Apply Functions during Update(): Changes the Vector2/Kinematics
	void ApplyGravity();
	void ApplyFriction();
	void ApplyDrag();

	float mass;									// Mass of Object
	float gravitationalForce;					// Strength of Gravitational Force

	//CoEfficients
	float co_Restitution;						// CoEfficient of Restitution(For Bounce)
	float co_KE, co_SE;							// CoEfficient of Static/Kinetic Friction
	float co_Drag;								// CoEfficient of Drag
	
	//Kinematics (Vector Values)
	Vector2* v_Pos;
	Vector2 v_Velocity;
	Vector2 v_Acceleration;
	Vector2 v_Force;

	//Max Magnitude of Kinematics/Vector Values
	const float MAX_VELOCITY = 700;
	const float MAX_ACCELERATION = 200;
	const float MAX_FORCE = 2000;

	//True = Enable Apply Functions
	bool isActive;								//Run Update
	bool hasFriction, hasDrag, hasGravity;		//Updates' Auto Apply Functions
	bool hasBounce, hasPush;					//Manual Apply Functions
};

#endif