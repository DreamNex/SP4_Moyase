#pragma once

#include <string>
#include "MeshBuilder.h"
#include "Scenes\SceneManager2D.h"

class ButtonUI
{
public:
	ButtonUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showText);
	~ButtonUI();
	
	Mesh* getNormalMesh();
	Mesh* getHoverMesh();

	std::string GetText();
	
	float GetSizeX();
	float GetSizeY();
	
	float GetX();
	float GetY();

	bool GetShowText();
	float GetTextScale();
	Vector3 GetTextPos();

	bool GetMouseover();
	void CheckMouseOver(float x, float y);

	void render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol = Color(0, 0, 0));
	
private:
	Mesh *normalMesh, *hoverMesh;
	float sizeX, sizeY;
	Vector3 pos, min, max;

	std::string text;
	float textScaling;
	Vector3 textOffset;
	bool showText;

	bool mouseover;
};