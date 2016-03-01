#pragma once

#include "../RigidBody/RigidBody.h"
#include "../Mesh.h"
#include "../Scenes/SceneManager2D.h"

class GameObject
{
public:
	GameObject();
	GameObject(Vector2 pos);
	virtual ~GameObject() = 0;

	void onDestory();

	virtual bool checkColision(GameObject *GO2);
	virtual void update(double dt);
	virtual void render(CSceneManager2D* SceneManager2D);

	void setPosition(Vector2 pos) 
	{
		this->pos = pos; 
	}

	RigidBody* getRigidBody() { return rigidBody; }
	Mesh* getMesh() { return this->mesh; }
	Vector2 getPos() { return this->pos; }
	Vector2* getPointerPos(){ return &pos; }

	bool GetApplyEffect(){ return this->applyEffect; }
	void SetApplyEffect(bool appEff){ this->applyEffect = appEff; }

protected:
	RigidBody* rigidBody;
	Mesh* mesh;
	Vector2 pos;
	bool applyEffect;
};