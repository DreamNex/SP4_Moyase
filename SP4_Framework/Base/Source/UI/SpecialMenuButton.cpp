#include "SpecialMenuButton.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

SpecialMenuButton::SpecialMenuButton(std::string text, float sizeX, float sizeY, float x, float y, float textScaling)
{
	this->text = text;
	this->textScaling = sizeX * textScaling;
	textOffset.Set(x - (this->textScaling / 2 * this->text.size() / 2), y - sizeY / 2);

	this->mesh = MeshBuilder::Generate2DMesh("", Color(0.847f, 0.529f, 0.941f), 0, 0, (int)sizeX, (int)sizeY);

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	pos.Set(x, y);
	min.Set(x - sizeX / 2, y - sizeY / 2);
	max.Set(x + sizeX / 2, y + sizeY / 2);
	mouseover = false;

	transparent = 100.f;
	increasing = false;
}

SpecialMenuButton::~SpecialMenuButton()
{
	delete mesh;
}

std::string SpecialMenuButton::GetText()
{
	return text;
}

bool SpecialMenuButton::CheckMouseOver(float x, float y, double dt)
{
	if (x > min.x && x < max.x && y > min.y && y < max.y)
	{
		if (transparent > 93)
		{
			increasing = false;
		}
		else if (transparent < 83)
		{
			increasing = true;
		}

		if (increasing)
		{
			transparent += dt * 60;
		}
		else
		{
			transparent -= dt * 60;
		}

		mouseover = true;
		return true;
	}
	else
	{
		increasing = false;

		if (transparent < 100)
		{
			transparent += dt * 7;
			if (transparent > 100)
				transparent = 100;
		}
		mouseover = false;
		return false;
	}
}

bool SpecialMenuButton::GetMouseover()
{
	return mouseover;
}

void SpecialMenuButton::render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol, float z)
{
	SceneManager2D->RenderMeshIn2DTrans(mesh, (int)(transparent), 1, 1, pos.x, pos.y, z, 0, -sizeX / 2, -sizeY / 2);
	
	SceneManager2D->RenderTextOnScreenTrans(textMesh, text, Color(1,1,1), (int)(0), textScaling, textOffset.x, textOffset.y, z);
}