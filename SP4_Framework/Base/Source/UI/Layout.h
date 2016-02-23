#pragma once

#include <string>
#include "../MeshBuilder.h"
#include "../Scenes\SceneManager2D.h"
#include "Vector2.h"

class Layout
{
public:
	Layout(char* Mesh, float sizeX, float sizeY, float x, float y);
	~Layout();
	
	Mesh* getMesh();
	
	float GetSizeX();
	float GetSizeY();
	
	float GetX();
	float GetY();

	void render(CSceneManager2D* SceneManager2D, float z = 0);

private:
	Mesh *Mesh;
	float sizeX, sizeY;
	Vector2 pos;
};