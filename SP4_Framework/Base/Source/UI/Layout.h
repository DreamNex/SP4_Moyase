#pragma once

#include <string>
#include "../MeshBuilder.h"
#include "../Scenes\SceneManager2D.h"
#include "Vector2.h"

class Layout
{
public:
	Layout(char* Mesh, float sizeX, float sizeY, float x, float y, bool alphaMode = false, float transparent = 0, Color c = Color(0, 0, 0));
	~Layout();
	
	Mesh* getMesh();
	
	float GetSizeX();
	float GetSizeY();
	void setScale(float x, float y);

	Vector2 GetPos();
	void SetPos(float x, float y);

	void setAlphaMode(bool b) { alphaMode = b; }
	bool getAlphaMode() { return alphaMode; }

	void setTransparent(float i) { transparent = i; }
	float getTransparent() { return transparent; }

	void goTransparent(double dt, float multiplier);
	void goOpaque(double dt, float multiplier);

	void render(CSceneManager2D* SceneManager2D, float z = 0);

private:
	Mesh *Mesh;
	float sizeX, sizeY;
	Vector2 pos;

	bool alphaMode;
	float transparent;
};