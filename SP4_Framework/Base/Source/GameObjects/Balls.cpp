#include "Balls.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"
#include "../Application.h"

#include "Wall.h"
#include "Spikes.h"
#include "Cannon.h"
#include "Boost.h"
#include "Slow.h"
#include "Rebound.h"
#include "Wall.h"

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
		if (dynamic_cast<Wall*>(GO2))
		{
			if (Application::Button_Right == false)
				Application::SFX.Play("SoundTracks//bounce.mp3", false, false);
		}
		else if (dynamic_cast<Spikes*>(GO2))
		{

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

				Application::SFX.Play("SoundTracks//CannonFiring.mp3", false, false);

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
				Application::SFX.Play("SoundTracks//BoostTrack.mp3", false, false);
				this->getRigidBody()->GetPhysicsCompt()->SetVelocity(this->getRigidBody()->GetPhysicsCompt()->GetVelocity() * 2);
				dynamic_cast<Boost*>(GO2)->setColided(true);
			}
		}
		else if (dynamic_cast<Slow*>(GO2))
		{
			if (!dynamic_cast<Slow*>(GO2)->getColided())
			{
				Application::SFX.Play("SoundTracks//SlowTrack.mp3", false, false);
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


std::vector<Vector2> Balls::GetPath(std::vector<GameObject*> levelAssets, Vector2 start, Vector2 force, float dt, float frequency, float life)
{
	std::vector<Vector2> pathPoints;
	Vector2 currentPoint;

	GameObject* temp_GO = new Balls(start, ((Circle*)this->getRigidBody()->GetCollisionCompt())->GetRadius(), "Image//Avatar//Avatar_1");
	temp_GO->getRigidBody()->GetPhysicsCompt()->SetForce(Vector2(0, 0));
	temp_GO->getRigidBody()->GetPhysicsCompt()->SetVelocity(Vector2(0, 0));
	temp_GO->getRigidBody()->GetPhysicsCompt()->SetAcceleration(Vector2(0, 0));
	temp_GO->getRigidBody()->GetPhysicsCompt()->Push(force);


	float frequency_Copy = frequency;
	while (life > 0)
	{
		temp_GO->update(dt);
		for (unsigned int i = 0; i < levelAssets.size(); ++i)
		{ 
			if (dynamic_cast<Wall*>(levelAssets[i]))
			{ 
				if (temp_GO->checkColision(levelAssets[i]))
				{
					if (temp_GO->getRigidBody()->GetPhysicsCompt()->GetActive() == false)
						return pathPoints;
				}
			}
		}

		pathPoints.push_back(currentPoint);

		if (frequency <= 0)
		{
			frequency = frequency_Copy;
			currentPoint = temp_GO->getPos();
		}
		frequency -= dt;
		life -= dt;
	}
	return pathPoints;
}

