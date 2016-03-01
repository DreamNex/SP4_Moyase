#include "SliderUI.h"
#include "GL/glew.h"
#include "../LoadTGA.h"
//#include "../Application.h"

SliderUI::SliderUI(char* SMesh, char* KMesh, float sizeX, float sizeY, Vector2 pos, float NormalizedVal)
{
	this->SMesh = MeshBuilder::Generate2DMesh("", Color(1.f, 1.f, 1.f), 0, 0, (int)sizeX, (int)sizeY);
	this->SMesh->textureID = LoadTGA(SMesh);

	this->KMesh = MeshBuilder::Generate2DMesh("", Color(1.f, 1.f, 1.f), 0, 0, (int)(sizeY + 10), (int)(sizeY + 10));
	this->KMesh->textureID = LoadTGA(KMesh);

	this->sizeX = sizeX;
	this->sizeY = sizeY;

	this->pos.x = pos.x;
	this->pos.y = pos.y;

	min.Set(pos.x - (sizeX * 0.5f), pos.y - (sizeY * 0.5f));
	max.Set(pos.x + (sizeX * 0.5f), pos.y + (sizeY * 0.5f));

	this->knobPos.y = pos.y - 5.f;
	this->knobPos.x = min.x + sizeX * NormalizedVal;

	knobMin.Set(knobPos.x - ((sizeY +10) * 0.5f), knobPos.y - ((sizeY +10) * 0.5f));
	knobMax.Set(knobPos.x + ((sizeY + 10) * 0.5f), knobPos.y + ((sizeY + 10) * 0.5f));
	//Application::BGM_Engine->getSoundVolume();
	hoverover = false;
	currentfilled = 0.f;
	total = 0.f;
	result = 0.f;
}

SliderUI::~SliderUI()
{
	delete SMesh;
}

bool SliderUI::CheckMouseOver(float x, float y)
{
	if (x > knobMin.x && x < knobMax.x && y > knobMin.y && y < knobMax.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SliderUI::Update(float x, float y, bool clicked, double dt)
{
	if (CheckMouseOver(x, y) && !clicked)
	{
		hoverover = true;
		return false;
	}

	else if (!CheckMouseOver(x, y) && !clicked && hoverover)
	{
		hoverover = false;
		return false;
	}

	if (hoverover && clicked)
	{
		DragKnob(x);
		return true;
	}

	

}

void SliderUI::DragKnob(float x)
{
	knobPos.x = x;
	knobMin.x = knobPos.x - sizeY*0.5;
	knobMax.x = knobPos.x + sizeY*0.75;
	if (knobPos.x <= min.x)
	{
		knobPos.x = min.x;
		knobMin.x = knobPos.x - sizeY*0.5;
		knobMax.x = knobPos.x + sizeY*0.75;
	}

	else if (knobPos.x >= max.x)
	{
		knobPos.x = max.x;
		knobMin.x = knobPos.x - sizeY*0.5;
		knobMax.x = knobPos.x + sizeY*0.75;
	}
}
//Get mesh
Mesh* SliderUI::GetSMesh()
{
	return SMesh;
}
//Get SizeX
float SliderUI::GetSizeX()
{
	return sizeX;
}
//Get SizeY
float SliderUI::GetSizeY()
{
	return sizeY;
}
//Get position
Vector2 SliderUI::GetPos()
{
	return pos;
}

void SliderUI::render(CSceneManager2D* SceneManager2D, float z)
{
	SceneManager2D->RenderMeshIn2D(SMesh, false, 1, 1, pos.x, pos.y, z, 0, -sizeX * 0.5f, -sizeY * 0.5f);
	SceneManager2D->RenderMeshIn2D(KMesh, false, 1, 1, knobPos.x, knobPos.y, z+1, 0, -sizeY * 0.5f, -sizeY * 0.5f);
}

float SliderUI::CalculateNumeral()
{
	currentfilled = knobPos.x - min.x;
	total = max.x - min.x;

	result = (currentfilled / total) * 100;

	return result;
}

Vector2 SliderUI::CalculatePosX(float numeral)
{
	total = max.x - min.x;
	currentfilled = numeral * total;
	knobPos.x = currentfilled + min.x;

	return knobPos;
}