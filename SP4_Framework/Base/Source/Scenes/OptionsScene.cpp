#include "OptionsScene.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include <sstream>

OptionsScene::OptionsScene()
{
}

OptionsScene::OptionsScene(int m_window_width, int m_window_height)
:
 CSceneManager2D(m_window_width, m_window_height)
{
}

OptionsScene::~OptionsScene()
{
	for (unsigned int i = 0; i < Sliders.size(); i++)
	{
		if (Sliders[i])
		{
			delete Sliders[i];
		}
	}
}

void OptionsScene::Init()
{
	CSceneManager2D::Init();
	//SM->Init();

	meshList[GEO_SPLASH] = MeshBuilder::Generate2DMesh("GEO_SPLASH", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_SPLASH]->textureID = LoadTGA("Image//game_bg.tga");
	
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("BGM", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	Sliders.push_back(new SliderUI("Image//Tits//btn.tga", "Image//Tits//btn_faded.tga",400, 40, Vector2(m_window_width * 0.5f, m_window_height * 0.5f), 0.5));
	Sliders.push_back(new SliderUI("Image//Tits//btn.tga", "Image//Tits//btn_faded.tga", 400, 40, Vector2(m_window_width * 0.5f, m_window_height * 0.5f - 60), 0.5));
}

void OptionsScene::Update(double dt)
{
	CSceneManager2D::Update(dt);

	for (unsigned int i = 0; i < Sliders.size(); i++)
	{
		Sliders[i]->Update((float)Application::mouse_current_x, m_window_height - (float)Application::mouse_current_y, Application::Button_Left, dt);
	}
}

void OptionsScene::Render()
{
	CSceneManager2D::Render();

	modelStack.PushMatrix();
	RenderMeshIn2D(meshList[GEO_SPLASH], false);
	modelStack.PopMatrix();

	for (unsigned int i = 0; i < Sliders.size(); i++)
	{
		Sliders[i]->render(this, 2);
	}

	//On screen text
	RenderTextOnScreen(meshList[GEO_TEXT], "BGM ", Color(0, 0, 0), 50, m_window_width * 0.5 - 300, m_window_height * 0.5f - 25);
	RenderTextOnScreen(meshList[GEO_TEXT], "SFX ", Color(0, 0, 0), 50, m_window_width * 0.5 - 300, m_window_height * 0.5f - 75);
}

void OptionsScene::Exit()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}