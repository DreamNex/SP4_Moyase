#include "SceneManager2D_Menu.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include <sstream>

CSceneManager2D_Menu::CSceneManager2D_Menu()
{
}

CSceneManager2D_Menu::CSceneManager2D_Menu(int m_window_width, int m_window_height)
:
CSceneManager2D(m_window_width, m_window_height)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneManager2D_Menu::~CSceneManager2D_Menu()
{
	for (int i = 0; i < clickTexts.size(); ++i)
	{
		if (clickTexts[i])
			delete clickTexts[i];
	}
}

void CSceneManager2D_Menu::Init()
{
	CSceneManager2D::Init();

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GEO_SPLASH", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//menu_bg.tga");

	clickTexts.push_back(new ClickText("Start", 50, m_window_width * 0.45, m_window_height * 0.4));
	clickTexts.push_back(new ClickText("Exit", 50, m_window_width * 0.45, m_window_height * 0.32));
}

void CSceneManager2D_Menu::Update(double dt)
{
	CSceneManager2D::Update(dt);
}

void CSceneManager2D_Menu::Render()
{
	CSceneManager2D::Render();

	//On screen text
	modelStack.PushMatrix();
	modelStack.Scale(800, 600, 1);
	RenderMeshIn2D(meshList[GEO_BG], false);
	modelStack.PopMatrix();
	
	for (int i = 0; i < clickTexts.size(); ++i)
	{
		if (clickTexts[i]->GetMouseover())
			RenderTextOnScreen(meshList[GEO_TEXT], clickTexts[i]->GetName(), Color(1, 0, 0), clickTexts[i]->GetSize(), clickTexts[i]->GetX(), clickTexts[i]->GetY());
		else
			RenderTextOnScreen(meshList[GEO_TEXT], clickTexts[i]->GetName(), Color(1, 1, 0), clickTexts[i]->GetSize(), clickTexts[i]->GetX(), clickTexts[i]->GetY());
	}
}

void CSceneManager2D_Menu::Exit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}