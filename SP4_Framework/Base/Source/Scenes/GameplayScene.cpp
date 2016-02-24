#include "GameplayScene.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include <sstream>

CGameplayScene::CGameplayScene()
{
}

CGameplayScene::CGameplayScene(int m_window_width, int m_window_height)
:
CSceneManager2D(m_window_width, m_window_height)
{
}

CGameplayScene::~CGameplayScene()
{

}

void CGameplayScene::Init()
{
	CSceneManager2D::Init();

	curentState = S_Play;

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
}

void CGameplayScene::Update(double dt)
{
	switch (curentState)
	{
	case S_Play:
		if(Application::IsKeyPressed(VK_ESCAPE))
		{
			curentState = S_Pause;
		}
		break;

	case S_Pause:
		break;
	}
}

void CGameplayScene::Render()
{
	CSceneManager2D::Render();

	switch (curentState)
	{
	case S_Play:
		RenderTextOnScreen(meshList[GEO_TEXT], "Press esc to pause", Color(0, 1, 0), 50, 0, 0);
		break;

	case S_Pause:
		RenderTextOnScreen(meshList[GEO_TEXT], "Paused", Color(0, 1, 0), 50, 0, 0);
		break;
	}
}

void CGameplayScene::Exit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}