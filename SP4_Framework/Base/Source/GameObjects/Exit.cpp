#include "Exit.h"

#include "../MeshBuilder.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Exit::Exit(Vector2 pos, float width, float height)
: Enviroment(pos)
{
	this->rigidBody = new RigidBody(new Box(this->pos, width, height), new PhysicsComponent(this->pos, 1, false), false);
	this->mesh = MeshBuilder::Generate2DMesh("Mesh", Color(0, 1, 0), 0, 0, 1, 1);
	//this->mesh->textureID = LoadTGA(texturePath);

	trans = 20;
	goingup = true;
}

Exit::~Exit()
{
	onDestory();
}

void Exit::updateGraphics(double dt)
{
	if (trans < 20)
		goingup = true;
	else if (trans > 50)
		goingup = false;

	if (goingup)
		trans += dt * 40;
	else
		trans -= dt * 40;
}

void Exit::render(CSceneManager2D* SceneManager2D)
{
	SceneManager2D->Render2DMeshTrams(this->mesh, (int)trans, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - this->rigidBody->GetScale(0)*0.5f, this->pos.y - this->rigidBody->GetScale(1)*0.5f);
}