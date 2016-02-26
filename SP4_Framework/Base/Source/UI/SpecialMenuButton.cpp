#include "SpecialMenuButton.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

SpecialMenuButton::SpecialMenuButton(std::string text, float sizeX, float sizeY, float x, float y, float textScaling)
{
	this->text = text;
	this->textScaling = sizeY * textScaling;
	textOffset.Set(x - (this->textScaling / 2 * this->text.size() / 2), y - sizeY / 2 + textScaling);

	this->mesh = MeshBuilder::Generate2DMesh("", Color(1.f, 1.f, 1.f), 0, 0, (int)sizeX, (int)sizeY);

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	pos.Set(x, y);
	min.Set(x - sizeX / 2, y - sizeY / 2);
	max.Set(x + sizeX / 2, y + sizeY / 2);
	mouseover = false;

	transparent = 0.f;
	increasing = false;
}

SpecialMenuButton::~SpecialMenuButton()
{
	delete mesh;
}

bool SpecialMenuButton::CheckMouseOver(float x, float y, double dt)
{
	if (x > min.x && x < max.x && y > min.y && y < max.y)
	{
		if (transparent > 70)
		{
			increasing = false;
		}
		else if (transparent < 30)
		{
			increasing = true;
		}

		if (increasing)
		{
			transparent += dt * 100;
		}
		else
		{
			transparent -= dt * 100;
		}
		if (textOffset.y < max.y - textScaling)
		{
			textOffset.y += dt * sizeY * 0.1f;
		}

		mouseover = true;
		return true;
	}
	else
	{
		increasing = false;

		if (transparent > 0)
		{
			transparent -= dt * 70;
			if (transparent < 0)
				transparent = 0;
		}

		if (textOffset.y > min.y + textScaling)
		{
			textOffset.y += dt * sizeY * 0.1f;
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
	
	SceneManager2D->RenderTextOnScreenTrans(textMesh, text, textCol, (int)(transparent), textScaling, textOffset.x, textOffset.y, z);
}