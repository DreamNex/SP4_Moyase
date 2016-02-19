#include "GameObject.h"

GameObject::GameObject()
: rigidBody(NULL)
, mesh(NULL)
, pos(0, 0)
{
}

GameObject::GameObject(Vector2 pos)
{
	this->pos = pos;
}

GameObject::~GameObject()
{
}

void GameObject::onDestory()
{
	if (rigidBody)
		delete rigidBody;
	if (mesh)
		delete mesh;
}

bool GameObject::checkColision(GameObject *GO2)
{
	return this->rigidBody->CollideWith(GO2->getRigidBody());
}

void GameObject::update(double dt)
{
	this->rigidBody->Update(dt);
}

void GameObject::render(CSceneManager2D* SceneManager2D)
{
	float a = this->rigidBody->GetScale(0)*0.5;
	SceneManager2D->RenderMeshIn2D(this->mesh, false, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - this->rigidBody->GetScale(0)*0.5, this->pos.y - this->rigidBody->GetScale(1)*0.5);
}