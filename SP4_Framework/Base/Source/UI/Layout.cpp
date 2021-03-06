#include "Layout.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Layout::Layout(char* mesh, float sizeX, float sizeY, float x, float y, bool alphaMode, float transparent, Color c)
{
	this->Mesh = MeshBuilder::Generate2DMesh("", c, 0, 0, (int)1, (int)1);
	if (mesh != "")
		this->Mesh->textureID = LoadTGA(mesh);

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	pos.Set(x, y);

	this->alphaMode = alphaMode;
	this->transparent = transparent;
}

Layout::~Layout()
{
	delete Mesh;
}

Mesh* Layout::getMesh()
{ 
	return Mesh; 
}

float Layout::GetSizeX()
{
	return sizeX;
}

float Layout::GetSizeY()
{
	return sizeY;
}

void Layout::setScale(float x, float y)
{
	sizeX = x;
	sizeY = y;
}

Vector2 Layout::GetPos()
{
	return pos;
}

void Layout::SetPos(float x, float y)
{
	pos.x = x; 
	pos.y = y;
}

void Layout::goTransparent(double dt, float multiplier)
{ 
	if (alphaMode && transparent < 100) 
	{ 
		transparent += dt * multiplier; 
		if (transparent > 100) 
			transparent = 100; 
	}
}

void Layout::goOpaque(double dt, float multiplier)
{ 
	if (alphaMode && transparent > 0)
	{
		transparent -= dt * multiplier;
		if (transparent < 0)
			transparent = 0;
	}
}

void Layout::render(CSceneManager2D* SceneManager2D, float z)
{
	if (alphaMode)
		SceneManager2D->RenderMeshIn2DTrans(Mesh, (int)(transparent), sizeX, sizeY, pos.x - sizeX / 2, pos.y - sizeY / 2, z);
	else
		SceneManager2D->RenderMeshIn2D(Mesh, false, sizeX, sizeY, pos.x - sizeX / 2, pos.y - sizeY / 2, z);
}