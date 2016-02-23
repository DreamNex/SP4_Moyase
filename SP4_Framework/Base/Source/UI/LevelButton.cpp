#include "LevelButton.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

LevelButton::LevelButton(std::string levelName, bool unlock, std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showText)
:ButtonUI(text, normalMesh, hoverMesh, sizeX, sizeY, x, y, textScaling, showText)
{
	this->levelName = levelName;
	this->unlock = unlock;
	
	this->lockMesh = MeshBuilder::Generate2DMesh("", Color(1.f, 1.f, 1.f), 0, 0, (int)sizeX, (int)sizeY);
	this->lockMesh->textureID = LoadTGA("Image//lock.tga");
}

LevelButton::~LevelButton()
{
	delete lockMesh;
}

void LevelButton::render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol, float z)
{
	if (unlock)
	{
		if (mouseover)
			SceneManager2D->RenderMeshIn2D(hoverMesh, false, 1, 1, pos.x, pos.y, z, 0, -sizeX / 2, -sizeY / 2);
		else
			SceneManager2D->RenderMeshIn2D(normalMesh, false, 1, 1, pos.x, pos.y, z, 0, -sizeX / 2, -sizeY / 2);
		if (showText)
			SceneManager2D->RenderTextOnScreen(textMesh, text, textCol, textScaling, textOffset.x, textOffset.y, z);
	}
	else
		SceneManager2D->RenderMeshIn2D(lockMesh, false, 1, 1, pos.x, pos.y, z, 0, -sizeX / 2, -sizeY / 2);
}