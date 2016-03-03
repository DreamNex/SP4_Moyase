#pragma once

#include <string>
#include "../MeshBuilder.h"
#include "../Scenes\SceneManager2D.h"
#include "Vector2.h"

class SpecialMenuButton
{
public:
	SpecialMenuButton(std::string text, float sizeX, float sizeY, float x, float y, float textScaling = 0);
	~SpecialMenuButton();

	std::string GetText();

	bool GetMouseover();
	bool CheckMouseOver(float x, float y, double dt);

	void Update(double dt);

	void render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol = Color(0, 0, 0), float z = 0);
	
protected:
	Mesh *mesh;
	float sizeX, sizeY;
	Vector2 pos, min, max;

	std::string text;
	float textScaling;
	Vector2 textOffset;

	bool mouseover;

	float transparent;
	bool increasing;
};