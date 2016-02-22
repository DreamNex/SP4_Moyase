#include "Cannon.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Cannon::Cannon(Vector2 pos, float width, float height)
: Tools(pos)
, angle(0)
{
	this->rigidBody = new RigidBody(new Box(this->pos, width, height), new PhysicsComponent(this->pos, 1, false), true, false, false);
	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0.741, 0, 0.470), 0, 0, 1, 1);
	this->mesh->textureID = LoadTGA("Image//Cannon.tga");
}

Cannon::~Cannon()
{
	onDestory();
}

/*void Cannon::render(CSceneManager2D* SceneManager2D)
{
	SceneManager2D->RenderMeshIn2D(this->mesh, false, this->rigidBody->GetScale(0) - 10, this->rigidBody->GetScale(1) - 10, this->pos.x - this->rigidBody->GetScale(0)*0.5 + 5, this->pos.y - this->rigidBody->GetScale(1)*0.5 + 5, this->angle);
}*/