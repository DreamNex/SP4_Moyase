#include "Wall.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Wall::Wall(Vector2 pos, float width, float height)
: Enviroment(pos)
{
	this->rigidBody = new RigidBody(new Box(this->pos, width, height), new PhysicsComponent(this->pos, 1, false), true);
	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0, 0, 0), 0, 0, 1, 1);
	//this->mesh->textureID = LoadTGA(texturePath);
}

Wall::~Wall()
{
	onDestory();
}