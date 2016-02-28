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

	if (transition)
		delete transition;
}

void CSceneManager2D_Menu::Init()
{
	CSceneManager2D::Init();

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GB", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//Tits//MainMenuBG.tga");

	int temp = m_window_width / 4;
	Buttons.push_back(new SpecialMenuButton("Start", temp * 0.5f, 200, temp, 200 * 0.5f, 0.2f));
	Buttons.push_back(new SpecialMenuButton("How 2 Play", temp * 0.5f, 300, temp + temp - temp*0.33f, 300 * 0.5f, 0.2f));
	Buttons.push_back(new SpecialMenuButton("Options", temp * 0.5f, 250, temp + temp + temp*0.33f, 250 * 0.5f, 0.2f));
	Buttons.push_back(new SpecialMenuButton("Exit", temp * 0.5f, 150, temp + temp + temp, 150 * 0.5f, 0.2f));

	transition = new Layout("", m_window_width, m_window_height, m_window_width * 0.5f, m_window_height * 0.5f, true);
}

void CSceneManager2D_Menu::Update(double dt)
{
	CSceneManager2D::Update(dt);

	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		if (Buttons[i]->CheckMouseOver((float)Application::mouse_current_x, (float)Application::mouse_current_y, dt));
	}
}

void CSceneManager2D_Menu::Render()
{
	CSceneManager2D::Render();

	modelStack.PushMatrix();
	RenderMeshIn2D(meshList[GEO_BG], false, 1, 1, 0, 0, -1);
	modelStack.PopMatrix();

	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		Buttons[i]->render(this, meshList[GEO_TEXT]);
	}

	transition->render(this, 1);
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