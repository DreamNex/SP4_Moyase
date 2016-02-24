#include "Layout.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

Layout::Layout(char* Mesh, float sizeX, float sizeY, float x, float y)
{
	this->Mesh = MeshBuilder::Generate2DMesh("", Color(1.f, 1.f, 1.f), 0, 0, (int)sizeX, (int)sizeY);
	this->Mesh->textureID = LoadTGA(Mesh);

	this->sizeX = sizeX;
	this->sizeY = sizeY;
	pos.Set(x, y);
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

float Layout::GetX()
{
	return pos.x;
}

float Layout::GetY()
{
	return pos.y;
}

void Layout::render(CSceneManager2D* SceneManager2D, float z)
{
	SceneManager2D->RenderMeshIn2D(Mesh, false, 1, 1, pos.x - sizeX / 2, pos.y - sizeY / 2, z);
}