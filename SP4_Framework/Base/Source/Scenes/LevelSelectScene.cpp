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

	currentPage = 0;
	numOfPage = 0;
}

CLevelSelectScene::~CLevelSelectScene()
{
	if (mainLayout)
		delete mainLayout;

	if (levelLayout)
		delete levelLayout;

	if (FileReader)
		delete FileReader;

	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		if (Buttons[i])
			delete Buttons[i];
	}

	for (unsigned int i = 0; i < LevelButtons.size(); ++i)
	{
		for (unsigned int j = 0; j < LevelButtons[i].size(); ++j)
		{
			if (LevelButtons[i][j])
				delete LevelButtons[i][j];
		}
	}
}

void CLevelSelectScene::Init()
{
	CSceneManager2D::Init();

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GB", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//Tits//MainMenuBG.tga");

	mainLayout = new Layout("Image//Tits//", m_window_width * 0.7, m_window_height * 0.7, m_window_width * 0.5, m_window_height * 0.5);
	levelLayout = new Layout("Image//Tits//btn.tga", mainLayout->GetSizeX() * 0.55, mainLayout->GetSizeY() * 0.7, mainLayout->GetX() * 0.7, mainLayout->GetY() * 0.9);

	FileReader = new FileReading();
	std::vector<string> levelNames = FileReader->SearchFolder("Levels//");

	numOfPage = levelNames.size()/6 + 1;
	if (levelNames.size() % 6 == 0)
		numOfPage--;
	
	LevelButtons.resize(numOfPage);

	int curPage = 0;
	bool unlock;
	Vector2 pos;

	for (int i = 0; i < levelNames.size(); ++i)
	{
		FileReader->loadFile("Levels//" + levelNames[i]);
		FileReader->loadVariables(unlock);

		switch (i % 6)
		{
		case 0:
			{
				  if (i != 0)
					  curPage++;
				  pos.Set(levelLayout->GetX() - levelLayout->GetSizeX()/4, levelLayout->GetY() + levelLayout->GetSizeY()/6);
				  break;
			}
		case 1:
			{
				  pos.Set(levelLayout->GetX(), levelLayout->GetY() + levelLayout->GetSizeY() / 6);
				  break;
			}
		case 2:
			{
				  pos.Set(levelLayout->GetX() + levelLayout->GetSizeX() / 4, levelLayout->GetY() + levelLayout->GetSizeY() / 6);
				  break;
			}
		case 3:
			{
				  pos.Set(levelLayout->GetX() - levelLayout->GetSizeX() / 4, levelLayout->GetY() - levelLayout->GetSizeY() / 6);
				  break;
			}
		case 4:
			{
				  pos.Set(levelLayout->GetX(), levelLayout->GetY() - levelLayout->GetSizeY() / 6);
				  break;
			}
		case 5:
			{
				  pos.Set(levelLayout->GetX() + levelLayout->GetSizeX() / 4, levelLayout->GetY() - levelLayout->GetSizeY() / 6);
				  break;
			}
		}
		LevelButtons[curPage].push_back(new LevelButton(levelNames[i]
			, unlock
			, std::to_string(i + 1)
			, "Image//Tits//btn.tga", "Image//Tits//btn_faded.tga"
			, levelLayout->GetSizeX() * 0.15, levelLayout->GetSizeX() * 0.15
			, pos.x, pos.y
			, 0.6, true));
	}

	Buttons.push_back(new ButtonUI("LevelLeft"
		, "Image//arrow.tga", "Image//arrow_hover.tga"
		, levelLayout->GetSizeX() * 0.1, levelLayout->GetSizeX() * 0.1
		, levelLayout->GetX() - levelLayout->GetSizeX() / 2.5, levelLayout->GetY()
		, 0.6, false
		, 180));

	Buttons.push_back(new ButtonUI("LevelRight"
		, "Image//arrow.tga", "Image//arrow_hover.tga"
		, levelLayout->GetSizeX() * 0.1, levelLayout->GetSizeX() * 0.1
		, levelLayout->GetX() + levelLayout->GetSizeX() / 2.5, levelLayout->GetY()
		, 0.6, false));
}

void CLevelSelectScene::Update(double dt)
{
	CSceneManager2D::Update(dt);
}

void CLevelSelectScene::Render()
{
	CSceneManager2D::Render();
	
	modelStack.PushMatrix();
	RenderMeshIn2D(meshList[GEO_BG], false);
	modelStack.PopMatrix();

	mainLayout->render(this, 1);

	levelLayout->render(this, 2);

	//Buttons[0]->render(this, meshList[GEO_TEXT], Color(0, 0, 0));
	for (int i = 0; i < Buttons.size(); i++)
	{
		Buttons[i]->render(this, meshList[GEO_TEXT], Color(0, 0, 0), 3);
	}

	for (int i = 0; i < LevelButtons[currentPage].size(); i++)
	{
		LevelButtons[currentPage][i]->render(this, meshList[GEO_TEXT], Color(0, 0, 0), 3);
	}
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