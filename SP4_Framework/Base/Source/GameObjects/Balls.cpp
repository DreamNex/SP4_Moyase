#include "Balls.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

#include "Spikes.h"
#include "Cannon.h"
#include "Boost.h"
#include "Slow.h"
#include "Rebound.h"

Balls::Balls(Vector2 pos, float diameter, const char* texturePath)
: GameObject(pos)
{
	originalPos = pos;
	this->rigidBody = new RigidBody(new Circle(this->pos, diameter * 0.5f), new PhysicsComponent(this->pos, 5.f, true), true);

	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0, 0, 0), 0, 0, 1, 1);
	this->mesh->textureID = LoadTGA(texturePath);
}

Balls::~Balls()
{
	onDestory();
}

bool Balls::checkColision(GameObject *GO2)
{
	if (this->rigidBody->CollideWith(GO2->getRigidBody()))
	{
		SpecialcolisionResponce(GO2);
		return true;
	}
	else if (dynamic_cast<Tools*>(GO2))
	{
		dynamic_cast<Tools*>(GO2)->reset();
	}
	return false;
}

void Balls::SpecialcolisionResponce(GameObject *GO2)
{
	if (dynamic_cast<Enviroment*>(GO2))
	{
		if (dynamic_cast<Spikes*>(GO2))
		{
			this->pos = originalPos;
		}
		else if (dynamic_cast<Rebound*>(GO2))
		{
			dynamic_cast<Rebound*>(GO2)->activateWave();

			Vector2 dir = (this->pos - GO2->getPos()).Normalized();

			if (this->getRigidBody()->GetPhysicsCompt()->GetVelocity().Length()*0.2 < 50)
				this->getRigidBody()->GetPhysicsCompt()->Push(dir * 50);
			else
				this->getRigidBody()->GetPhysicsCompt()->Push(dir * (this->getRigidBody()->GetPhysicsCompt()->GetVelocity().Length()*0.2));
		}
	}
	else if (dynamic_cast<Tools*>(GO2))
	{
		if (dynamic_cast<Cannon*>(GO2))
		{
			if (!dynamic_cast<Cannon*>(GO2)->getColided())
			{
				this->getRigidBody()->GetPhysicsCompt()->SetForce(Vector2(0, 0));
				this->getRigidBody()->GetPhysicsCompt()->SetVelocity(Vector2(0, 0));
				this->getRigidBody()->GetPhysicsCompt()->SetAcceleration(Vector2(0, 0));
				this->pos = GO2->getPos();

				Vector2 dir(0, ((Cannon*)(GO2))->GetPower());
				dir.rotateVector(dynamic_cast<Cannon*>(GO2)->getAngleByReference());

				this->getRigidBody()->GetPhysicsCompt()->Push(dir);

				dynamic_cast<Cannon*>(GO2)->setColided(true);
			}
		}
		else if (dynamic_cast<Boost*>(GO2))
		{
			if (!dynamic_cast<Boost*>(GO2)->getColided())
			{
				this->getRigidBody()->GetPhysicsCompt()->SetVelocity(this->getRigidBody()->GetPhysicsCompt()->GetVelocity() * 2);
				dynamic_cast<Boost*>(GO2)->setColided(true);
			}
		}
		else if (dynamic_cast<Slow*>(GO2))
		{
			if (!dynamic_cast<Slow*>(GO2)->getColided())
			{
				this->getRigidBody()->GetPhysicsCompt()->SetVelocity(this->getRigidBody()->GetPhysicsCompt()->GetVelocity() * 0.3);
				dynamic_cast<Slow*>(GO2)->setColided(true);
			}
		}
	}
}

void Balls::reset()
{
	pos = originalPos;
	this->getRigidBody()->GetPhysicsCompt()->SetForce(Vector2(0, 0));
	this->getRigidBody()->GetPhysicsCompt()->SetVelocity(Vector2(0, 0));
	this->getRigidBody()->GetPhysicsCompt()->SetAcceleration(Vector2(0, 0));
	this->getRigidBody()->GetPhysicsCompt()->SetActive(true);
}