#include "GUI.h"


GUI::GUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showTex)
	: BtnIsActive(false)
	, ButtonUI(text,normalMesh,hoverMesh, sizeX,sizeY,x,  y,  textScaling,  showTex)
{
}


GUI::~GUI()
{
}

bool GUI::GetActive()
{
	return BtnIsActive;
}
void GUI::SetActive(bool Active)
{
	this->BtnIsActive = Active;
}