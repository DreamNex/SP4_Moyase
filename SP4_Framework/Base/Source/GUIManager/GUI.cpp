#include "GUI.h"


GUI::GUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showTex, GUITYPEID GUITYPEID)
	: BtnIsActive(false)
	, ButtonUI(text,normalMesh,hoverMesh, sizeX,sizeY,x,  y,  textScaling,  showTex)
	, g_typeID(CANNONGUI)
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

void GUI::SetType(int g_typeID)
{
	this->g_typeID = g_typeID;
}

int GUI::GetType()
{
	return g_typeID;
}