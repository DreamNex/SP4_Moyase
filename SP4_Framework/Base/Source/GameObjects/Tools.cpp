#include "Tools.h"

Tools::Tools(Vector2 pos)
: GameObject(pos)
, collided(false)
, hovering(false)
{
}

Tools::~Tools()
{
	if (hoverMesh)
	{
		delete hoverMesh;
		hoverMesh = NULL;
	}
}

void Tools::render(CSceneManager2D* SceneManager2D)
{
	if (hovering)
		SceneManager2D->Render2DMesh(this->hoverMesh, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - this->rigidBody->GetScale(0)*0.5f, this->pos.y - this->rigidBody->GetScale(1)*0.5f);
	else
		SceneManager2D->Render2DMesh(this->mesh, this->rigidBody->GetScale(0), this->rigidBody->GetScale(1), this->pos.x - this->rigidBody->GetScale(0)*0.5f, this->pos.y - this->rigidBody->GetScale(1)*0.5f);
}