#include "Cannon.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Cannon::Cannon(Vector2& pos, float width, float height)
: Tools(pos)
, angle(0)
{
	this->rigidBody = new RigidBody(new Box(this->pos, width, height), new PhysicsComponent(this->pos, 1, false), false);

	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0.741, 0, 0.470), 0, 0, 1, 1);
	this->mesh->textureID = LoadTGA("Image//Cannon.tga");

	this->hoverMesh = MeshBuilder::Generate2DMesh("Mesh", Color(0.741, 0, 0.470), 0, 0, 1, 1);
	this->hoverMesh->textureID = LoadTGA("Image//Cannon_hover.tga");
	power = 1000;
}

Cannon::~Cannon()
{
	onDestory();
}

void Cannon::SetPower(float power)
{
	this->power = power;
}

void Cannon::render(CSceneManager2D* SceneManager2D)
{
	if (hovering)
		SceneManager2D->Render2DMesh(this->hoverMesh, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x, this->pos.y, this->angle, -this->rigidBody->GetScale(0) / 2, -this->rigidBody->GetScale(1) / 2);
	else
		SceneManager2D->Render2DMesh(this->mesh, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x, this->pos.y, this->angle, -this->rigidBody->GetScale(0) / 2, -this->rigidBody->GetScale(1) / 2);
}