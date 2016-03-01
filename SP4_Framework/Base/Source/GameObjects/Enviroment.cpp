#include "Enviroment.h"

Enviroment::Enviroment(Vector2 &pos)
: GameObject(pos)
{
}

Enviroment::~Enviroment()
{
}

void Enviroment::update(double dt)
{
	this->rigidBody->Update((float)dt);
}

void Enviroment::render(CSceneManager2D* SceneManager2D)
{
	SceneManager2D->Render2DMesh(this->mesh, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - this->rigidBody->GetScale(0)*0.5f, this->pos.y - this->rigidBody->GetScale(1)*0.5f);
}