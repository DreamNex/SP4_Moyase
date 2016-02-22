#include "Spikes.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Spikes::Spikes(Vector2 pos, float width, float height)
: Enviroment(pos)
{
	this->rigidBody = new RigidBody(new Box(this->pos, width, height), new PhysicsComponent(this->pos, 1, false), true);
	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0.741, 0, 0.470), 0, 0, 1, 1);
	this->outerMesh = MeshBuilder::Generate2DMesh("Mesh", Color(0, 1, 0), 0, 0, 1, 1);
	//this->mesh->textureID = LoadTGA(texturePath);
}

Spikes::~Spikes()
{
	onDestory();
	if (outerMesh)
		delete outerMesh;
}

void Spikes::render(CSceneManager2D* SceneManager2D)
{
	SceneManager2D->Render2DMesh(this->mesh, this->rigidBody->GetScale(0) - 10, this->rigidBody->GetScale(1) - 10, this->pos.x - this->rigidBody->GetScale(0)*0.5 + 5, this->pos.y - this->rigidBody->GetScale(1)*0.5 + 5);
	SceneManager2D->Render2DMesh(this->outerMesh, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - (this->rigidBody->GetScale(0)*0.5), this->pos.y - (this->rigidBody->GetScale(1)*0.5));

}