#include "Balls.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

#include "Spikes.h"

Balls::Balls(Vector2 pos, float diameter, char* texturePath)
: GameObject(pos)
{
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
		if (dynamic_cast<Spikes*>(GO2))
		{
			this->pos = dynamic_cast<Spikes*>(GO2)->getRespawnPos();
		}
		return true;
	}
	return false;
}

void SpecialcolisionResponce()
{

}