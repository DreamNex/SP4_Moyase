#include "GameObject.h"

GameObject::GameObject()
: rigidBody(NULL)
, mesh(NULL)
, pos(0, 0)
, applyEffect(false)
{
}

GameObject::GameObject(Vector2 pos)
{
	this->pos = pos;
	this->applyEffect = false;
}

GameObject::~GameObject()
{
	onDestory();
}

void GameObject::onDestory()
{
	if (rigidBody)
	{
		delete rigidBody;
		rigidBody = NULL;
	}
	if (mesh)
	{
		delete mesh;
		mesh = NULL;
	}
}

bool GameObject::checkColision(GameObject *GO2)
{
	return this->rigidBody->CollideWith(GO2->getRigidBody());
}

void GameObject::update(double dt)
{
	this->rigidBody->Update((float)dt);
}

void GameObject::render(CSceneManager2D* SceneManager2D)
{
	SceneManager2D->Render2DMesh(this->mesh, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - this->rigidBody->GetScale(0)*0.5f, this->pos.y - this->rigidBody->GetScale(1)*0.5f);
}