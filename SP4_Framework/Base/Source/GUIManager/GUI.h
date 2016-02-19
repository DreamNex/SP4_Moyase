#pragma once
#include "../ButtonUI.h"
#include <vector>

class GUI :
	public ButtonUI
{

private:
	bool BtnIsActive;
public:
	GUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showTex);
	~GUI();

	bool GetActive();
	void SetActive(bool Active);
};

