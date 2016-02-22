#include "LevelSelectScene.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include <sstream>

CLevelSelectScene::CLevelSelectScene()
{
}

CLevelSelectScene::CLevelSelectScene(int m_window_width, int m_window_height)
:
CSceneManager2D(m_window_width, m_window_height)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CLevelSelectScene::~CLevelSelectScene()
{
	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		if (Buttons[i])
			delete Buttons[i];
	}
}

void CLevelSelectScene::Init()
{
	CSceneManager2D::Init();

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GB", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//Tits//MainMenuBG.tga");


	Buttons.push_back(new ButtonUI("Start", "Image//Tits//btn.tga", "Image//Tits//btn_faded.tga", 150, 75, m_window_width / 2, m_window_height / 2, 0.6, true));
	Buttons.push_back(new ButtonUI("How 2 Play", "Image//Tits//btn.tga", "Image//Tits//btn_faded.tga", 150, 75, m_window_width / 2, m_window_height / 2 - 80, 0.35, true));
	Buttons.push_back(new ButtonUI("Options", "Image//Tits//btn.tga", "Image//Tits//btn_faded.tga", 150, 75, m_window_width / 2, m_window_height / 2 - 160, 0.5, true));
	Buttons.push_back(new ButtonUI("Exit", "Image//Tits//btn.tga", "Image//Tits//btn_faded.tga", 150, 75, m_window_width / 2, m_window_height / 2 - 240, 0.6, true));
}

void CLevelSelectScene::Update(double dt)
{
	CSceneManager2D::Update(dt);
}

void CLevelSelectScene::Render()
{
	CSceneManager2D::Render();
	
	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		Buttons[i]->render(this, meshList[GEO_TEXT]);
	}

	modelStack.PushMatrix();
	modelStack.Scale(800, 600, 1);
	RenderMeshIn2D(meshList[GEO_BG], false);
	modelStack.PopMatrix();
}

void CLevelSelectScene::Exit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}