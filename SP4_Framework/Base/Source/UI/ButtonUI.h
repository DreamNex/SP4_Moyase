#pragma once

#include <string>
#include "../MeshBuilder.h"
#include "../Scenes\SceneManager2D.h"
#include "Vector2.h"

class ButtonUI
{
public:
	ButtonUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling = 0, bool showText = false, float rotate = 0);
	~ButtonUI();
	
	Mesh* getNormalMesh();
	Mesh* getHoverMesh();

	std::string GetText();
	
	float GetSizeX();
	float GetSizeY();
	
	float GetX();
	float GetY();

	void SetPos(float x, float y);

	bool GetShowText();
	float GetTextScale();
	Vector2 GetTextPos();

	bool GetMouseover();
	bool CheckMouseOver(float x, float y);

	virtual void render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol = Color(0, 0, 0), float z = 0);
	
protected:
	Mesh *normalMesh, *hoverMesh;
	float sizeX, sizeY;
	Vector2 pos, min, max;

	std::string text;
	float textScaling;
	Vector2 textOffset;
	bool showText;

	bool mouseover;

	float rotate;
};