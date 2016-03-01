#include "LevelButton.h"
#include "GL\glew.h"
#include "../LoadTGA.h"

LevelButton::LevelButton(std::string levelName, bool unlock, std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showText, int socre)
:ButtonUI(text, normalMesh, hoverMesh, sizeX, sizeY, x, y, textScaling, showText)
{
	this->levelName = levelName;
	this->unlock = unlock;
	
	this->lockMesh = MeshBuilder::Generate2DMesh("", Color(1.f, 1.f, 1.f), 0, 0, (int)sizeX, (int)sizeY);
	this->lockMesh->textureID = LoadTGA("Image//lock.tga");
	
	this->HSMesh1 = MeshBuilder::Generate2DMesh("", Color(1.f, 1.f, 1.f), 0, 0, sizeX * 0.1f, sizeY * 0.15f);
	this->HSMesh1->textureID = LoadTGA("Image//highscore_indicator_1.tga");

	this->HSMesh2 = MeshBuilder::Generate2DMesh("", Color(1.f, 1.f, 1.f), 0, 0, sizeX * 0.1f, sizeY * 0.15f);
	this->HSMesh2->textureID = LoadTGA("Image//highscore_indicator_2.tga");

	hsScaleX = sizeX * 0.1f;
	hsScaleY = sizeY * 0.15f;

	this->score = socre;

}

LevelButton::~LevelButton()
{
	delete lockMesh;

	delete HSMesh1;
	delete HSMesh2;
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

		float dist = sizeX * 0.2f;

		for (int i = 0; i < 5; ++i)
		{
			if (i < score)
				SceneManager2D->RenderMeshIn2D(HSMesh2, false, 1, 1, this->min.x + dist * 0.5f + dist * i, min.y - hsScaleY, z, 0, -hsScaleX / 2, -hsScaleY / 2);
			else
				SceneManager2D->RenderMeshIn2D(HSMesh1, false, 1, 1, this->min.x + dist * 0.5f + dist * i, min.y - hsScaleY, z, 0, -hsScaleX / 2, -hsScaleY / 2);

		}
	}
	else
		SceneManager2D->RenderMeshIn2D(lockMesh, false, 1, 1, pos.x, pos.y, z, 0, -sizeX / 2, -sizeY / 2);
}