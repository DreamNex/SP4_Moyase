#include "Balls.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

#include "Spikes.h"
#include "Cannon.h"

Balls::Balls(Vector2 pos, float diameter, char* texturePath)
: GameObject(pos)
{
	originalPos = pos;
	this->rigidBody = new RigidBody(new Circle(this->pos, diameter * 0.5), new PhysicsComponent(this->pos, 1, true, true), true, true, true);

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
	}
	else if (dynamic_cast<Tools*>(GO2))
	{
		if (dynamic_cast<Cannon*>(GO2))
		{
			if (!dynamic_cast<Cannon*>(GO2)->getColided())
			{
				this->getRigidBody()->GetPhysicsCompt()->SetForce(Vector2(0, 0));
				this->getRigidBody()->GetPhysicsCompt()->SetVelocity(Vector2(0, 0));
				this->pos = GO2->getPos();

				Vector2 dir(0, 1);
				dir.rotateVector(dynamic_cast<Cannon*>(GO2)->getAngleByReference());
				this->getRigidBody()->GetPhysicsCompt()->ApplyForce(dir * 1000);

				dynamic_cast<Cannon*>(GO2)->setColided(true);
			}
		}
	}
}