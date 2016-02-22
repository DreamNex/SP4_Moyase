#include "ButtonUI.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

ButtonUI::ButtonUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showText)
{
	this->text = text;
	this->textScaling = sizeY * textScaling;
	textOffset.Set(x-(this->textScaling / 2 * this->text.size() / 2), y-(this->textScaling / 2), 0);
	this->showText = showText;

	this->normalMesh = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, sizeX, sizeY);
	this->normalMesh->textureID = LoadTGA(normalMesh);

	this->hoverMesh = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, sizeX, sizeY);
	this->hoverMesh->textureID = LoadTGA(hoverMesh);

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	pos.Set(x, y, 0);
	min.Set(x - sizeX / 2, y - sizeY / 2, 0);
	max.Set(x + sizeX / 2, y + sizeY / 2, 0);
	mouseover = false;
}

ButtonUI::~ButtonUI()
{
	delete normalMesh;
	delete hoverMesh;
}

bool ButtonUI::CheckMouseOver(float x, float y)
{
	if (x > min.x && x < max.x && y > min.y && y < max.y)
	{
		mouseover = true;
		return true;
	}
	else
	{
		mouseover = false;
		return false;
	}
}

Mesh* ButtonUI::getNormalMesh() 
{ 
	return normalMesh; 
}

Mesh* ButtonUI::getHoverMesh() 
{
	return hoverMesh; 
}

std::string ButtonUI::GetText()
{
	return text;
}

float ButtonUI::GetTextScale()
{
	return textScaling;
}

Vector3 ButtonUI::GetTextPos()
{
	return textOffset;
}

float ButtonUI::GetSizeX()
{
	return sizeX;
}

float ButtonUI::GetSizeY()
{
	return sizeY;
}

float ButtonUI::GetX()
{
	return pos.x;
}

float ButtonUI::GetY()
{
	return pos.y;
}

bool ButtonUI::GetShowText()
{
	return showText;
}

bool ButtonUI::GetMouseover()
{
	return mouseover;
}

void ButtonUI::render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol)
{
	if (mouseover)
		SceneManager2D->RenderMeshIn2D(hoverMesh, false, 1, 1, pos.x - sizeX / 2, pos.y - sizeY / 2);
	else
		SceneManager2D->RenderMeshIn2D(normalMesh, false, 1, 1, pos.x - sizeX / 2, pos.y - sizeY / 2);
	if (showText)
		SceneManager2D->RenderTextOnScreen(textMesh, text, textCol, textScaling, textOffset.x, textOffset.y);
}