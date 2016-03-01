#pragma once

#include <string>
#include "../MeshBuilder.h"
#include "../Scenes/SceneManager2D.h"
#include "Vector2.h"
#include <vector>

class SliderUI
{
public:
	SliderUI(char* SMesh, char* KMesh, float sizeX, float sizeY, Vector2 pos, float NormalizeValue);
	~SliderUI();

	Mesh* GetSMesh();
	Mesh* GetKMesh();

	float GetSizeX();
	float GetSizeY();

	Vector2 GetPos();

	float CalculateNumeral();
	Vector2 CalculatePosX(float numeral);

	bool CheckMouseOver(float x, float y);
	void DragKnob(float x);
	bool Update(float x, float y, bool clicked, double dt);

	virtual void render(CSceneManager2D* SceneManager2D, float z = 0);

protected:

	float currentfilled;
	float total;
	float result;
	Mesh* SMesh, *KMesh;
	float sizeX, sizeY;
	Vector2 pos, knobPos,  min, max, knobMin, knobMax;
	bool hoverover;
};