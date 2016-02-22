#include "Boost.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Boost::Boost(Vector2 pos, float width, float height)
: Tools(pos)
{
	this->rigidBody = new RigidBody(new Box(this->pos, width, height), new PhysicsComponent(this->pos, 1, false, false), false, false, false);
	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0.741, 0, 0.470), 0, 0, 1, 1);
	this->mesh->textureID = LoadTGA("Image//Blaze.tga");
}

Boost::~Boost()
{
	onDestory();
}