#pragma once

#include"GameObject.h"

class Tools : public GameObject
{
public:
	Tools(Vector2 pos);
	virtual ~Tools() = 0;

	void setColided(bool c) { collided = c; }
	bool getColided() { return collided; }

	virtual void reset() { collided = false; };
	virtual void render(CSceneManager2D* SceneManager2D);

	void setHovering(bool b) { hovering = b; }
protected:
	bool collided;

	Mesh* hoverMesh;
	bool hovering;
};