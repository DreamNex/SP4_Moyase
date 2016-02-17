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
	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		if (Buttons[i])
			delete Buttons[i];
	}
}

void CSceneManager2D_Menu::Init()
{
	CSceneManager2D::Init();

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GEO_SPLASH", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//menu_bg.tga");

	Buttons.push_back(new ButtonUI("Start", "Image//menu_bg.tga", "Image//calibri.tga", 200.f, 100.f, 400.f, 300.f, 0.6f, true));
	//Buttons.push_back(new Buttons("Exit", 50.f, m_window_width * 0.45f, m_window_height * 0.32f));
}

void CSceneManager2D_Menu::Update(double dt)
{
	CSceneManager2D::Update(dt);
}

void CSceneManager2D_Menu::Render()
{
	CSceneManager2D::Render();
	
	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		if (Buttons[i]->GetMouseover())
			RenderMeshIn2D(Buttons[i]->getHoverMesh(), false, 1, 1, Buttons[i]->GetX() - Buttons[i]->GetSizeX() / 2, Buttons[i]->GetY() - Buttons[i]->GetSizeY() / 2);
		else
			RenderMeshIn2D(Buttons[i]->getNormalMesh(), false, 1, 1, Buttons[i]->GetX() - Buttons[i]->GetSizeX() / 2, Buttons[i]->GetY() - Buttons[i]->GetSizeY() / 2);
		if (Buttons[i]->GetShowText())
		{
			RenderTextOnScreen(meshList[GEO_TEXT], Buttons[i]->GetText(), Color(0, 1, 0), Buttons[i]->GetTextScale(), Buttons[i]->GetTextPos().x, Buttons[i]->GetTextPos().y);
		}
	}

	modelStack.PushMatrix();
	modelStack.Scale(800, 600, 1);
	RenderMeshIn2D(meshList[GEO_BG], false);
	modelStack.PopMatrix();
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