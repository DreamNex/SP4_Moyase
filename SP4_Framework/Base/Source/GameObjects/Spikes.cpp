#include "Spikes.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Spikes::Spikes(Vector2 pos, float width, float height)
: Enviroment(pos)
{
	this->rigidBody = new RigidBody(new Box(this->pos, width, height), new PhysicsComponent(this->pos, 1, false), true);
	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0, 0, 0), 0, 0, 1, 1);
	this->outerMesh = MeshBuilder::Generate2DMesh("Mesh", Color(1, 0, 0), 0, 0, 1, 1);

	trans = 20;
	goingup = true;
}

Spikes::~Spikes()
{
	onDestory();
	if (outerMesh)
		delete outerMesh;
}

void Spikes::updateGraphics(double dt)
{
	if (trans < 20)
		goingup = true;
	else if (trans > 50)
		goingup = false;

	if (goingup)
		trans += dt * 60;
	else
		trans -= dt * 60;
}

void Spikes::render(CSceneManager2D* SceneManager2D)
{
	SceneManager2D->Render2DMeshTrams(this->outerMesh, (int)trans, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - (this->rigidBody->GetScale(0)*0.5f), this->pos.y - (this->rigidBody->GetScale(1) * 0.5f));
	SceneManager2D->Render2DMesh(this->mesh, this->rigidBody->GetScale(0) - 16.f, this->rigidBody->GetScale(1) - 16.f, this->pos.x - this->rigidBody->GetScale(0)*0.5f + 8.f, this->pos.y - this->rigidBody->GetScale(1)*0.5f + 8.f);
}