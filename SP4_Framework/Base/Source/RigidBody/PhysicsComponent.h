#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Vector2.h"
#include <vector>

class PhysicsComponent
{
public:
	//*************************************************************************************
	//CONSTRUCTOR(S) && DESTRUCTOR
	PhysicsComponent(Vector2 &v, float mass, bool active);
	PhysicsComponent(Vector2 &v, float mass, bool active, Vector2 force, Vector2 acc, Vector2 velo);
	PhysicsComponent();
	~PhysicsComponent();

	//*************************************************************************************
	//ACCESSOR(S)
	float GetMass(void)const;
	float GetGravitationalForce(void)const;

	float GetCoRestitution(void)const;
	float GetCoKinetic(void)const;
	float GetCoStatic(void)const;
	float GetCoDrag(void)const;

	Vector2 GetPosition(void)const;
	Vector2 GetVelocity(void)const;
	Vector2 GetAcceleration(void)const;
	Vector2 GetForce(void)const;

	bool GetActive(void)const;
	bool GetFriction(void)const;
	bool GetDrag(void)const;
	bool GetGravity(void)const;

	bool GetBounce(void)const;
	bool GetPush(void)const;

	//Get the Trajectory of Object
	std::vector<Vector2> GetTrajectory(Vector2, Vector2, float, float, float)const;

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

	//*************************************************************************************
	//MANUAL APPLY FUNCTIONS: Changes the Vector2/Kinematics outside Update
	void Push(Vector2);
	void toBounce(Vector2);
	void Update(float dt);

private:
	//*************************************************************************************
	//AUTO APPLY FUNCTIONS: Changes the Vector2/Kinematics inside Update
	void ApplyGravity();
	void ApplyFriction();
	void ApplyDrag();

	float mass;									// Mass of Object
	float gravitationalForce;					// Strength of Gravitational Force (Vertical Movement)

	//CoEfficients
	float co_Restitution;						// CoEfficient of Restitution (For Bounce)
	float co_KE, co_SE;							// CoEfficient of Static/Kinetic Friction (Horizontal Movement)
	float co_Drag;								// CoEfficient of Drag
	
	//Kinematics (Vector Values)
	Vector2* v_Pos;
	Vector2 v_Velocity;
	Vector2 v_Acceleration;
	Vector2 v_Force;

	//Max Magnitude of Kinematics/Vector Values
	const float MAX_VELOCITY = 500;
	const float MAX_ACCELERATION = 100;
	const float MAX_FORCE = 2000;

	//True = Enable Apply Functions
	bool isActive;								//Run Update
	bool hasFriction, hasDrag, hasGravity;		//Updates' Auto Apply Functions
	bool hasBounce, hasPush;					//Manual Apply Functions
};

#endif