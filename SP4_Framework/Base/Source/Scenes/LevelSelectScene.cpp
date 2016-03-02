#include "LevelSelectScene.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include "../Luala.h"
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

	curentState = S_Selecting;

	currentPage = 0;
	numOfPage = 0;

	currentAvatarImage = 0;
	totalAvatarImages = 0;
}

CLevelSelectScene::~CLevelSelectScene()
{
	if (levelLayout)
		delete levelLayout;

	if (AvatarLayout)
		delete AvatarLayout;

	if (selectedLayout)
		delete selectedLayout;

	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		for (unsigned int j = 0; j < Buttons[i].size(); ++j)
		{
			if (Buttons[i][j])
				delete Buttons[i][j];
		}
	}

	for (unsigned int i = 0; i < LevelButtons.size(); ++i)
	{
		for (unsigned int j = 0; j < LevelButtons[i].size(); ++j)
		{
			if (LevelButtons[i][j])
				delete LevelButtons[i][j];
		}
	}
	
	for (unsigned int i = 0; i < AvatarImages.size(); ++i)
	{
		if (AvatarImages[i])
			delete AvatarImages[i];
	}

	if (transition)
		delete transition;
}

void CLevelSelectScene::Init()
{
	CSceneManager2D::Init();

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GB", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//Tits//MainMenuBG.tga");

	//layout planes
	levelLayout = new Layout("Image//Untitled-4.tga", m_window_width * 0.48f, m_window_height * 0.48f, m_window_width * 0.36f, m_window_height * 0.5f, true, 10);
	AvatarLayout = new Layout("Image//i_pod.tga", m_window_width * 0.24f, m_window_height * 0.48f, m_window_width * 0.76f, m_window_height * 0.5f);
	selectedLayout = new Layout("", m_window_width * 0.4f, m_window_height * 0.5f, m_window_width * 0.5f, m_window_height * 0.5f, true, 40, Color(1, 1, 1));

	FileReading FileReader;

	Luala la("Playerpref.lua");
	volume1 = la.getFloat("BGM");
	volume2 = la.getFloat("SFX");

	Application::BGM.SetSoundVol(volume1);
	Application::SFX.SetSoundVol(volume2);

	if (!Application::isPlaying)
	{
		Application::BGM.Play("SoundTracks//MenuTrack.mp3", true, false);
		Application::isPlaying = true;
	}

	/***********************************************Search folder and load buttons******************************************************/
	std::vector<string> levelNames = FileReader.SearchFolder("Levels//", "*.txt");

	numOfPage = levelNames.size()/3 + 1;
	if (levelNames.size() % 3 == 0)
		numOfPage--;
	
	LevelButtons.resize(numOfPage);

	int curPage = 0;
	bool unlock;
	string score4lv;
	Vector2 pos;

	for (unsigned int i = 0; i < levelNames.size(); ++i)
	{
		FileReader.loadFile("Levels//" + levelNames[i]);
		FileReader.loadVariables(unlock);
		score4lv = FileReader.GetVariable("Levels//" + levelNames[i], "highscore");
		if (score4lv == "")
			score4lv = "0";
		else if (stoi(score4lv) < 0 || stoi(score4lv) > 5)
			score4lv = "0";
		switch (i % 3)
		{
		case 0:
			{
				  if (i != 0)
					  curPage++;
				  pos.Set(levelLayout->GetPos().x - levelLayout->GetSizeX() / 3.5, levelLayout->GetPos().y);
				  break;
			}
		case 1:
			{
				  pos.Set(levelLayout->GetPos().x, levelLayout->GetPos().y);
				  break;
			}
		case 2:
			{
				  pos.Set(levelLayout->GetPos().x + levelLayout->GetSizeX() / 3.5, levelLayout->GetPos().y);
				  break;
			}
		}
		LevelButtons[curPage].push_back(new LevelButton(levelNames[i]
			, unlock
			, levelNames[i].substr(0, levelNames[i].length() - 4)
			, "Image//disc.tga", "Image//disc_hover.tga"
			, levelLayout->GetSizeX() * 0.21, levelLayout->GetSizeX() * 0.21
			, pos.x, pos.y
			, 0.6, true, stoi(score4lv)));
	}
	/************************************************************************************************************************************/

	/******************************************Search folder and load avatar images******************************************************/
	std::vector<string> Images = FileReader.SearchFolder("Image//Avatars//", "*.tga");
	totalAvatarImages = Images.size();

	for (unsigned int i = 0; i < Images.size(); ++i)
	{
		AvatarImages.push_back(MeshBuilder::Generate2DMesh(Images[i], Color(0, 0, 0), 0, 0, AvatarLayout->GetSizeX() * 0.4f, AvatarLayout->GetSizeX() * 0.4f));
		AvatarImages.back()->textureID = LoadTGA(("Image//Avatars//" + Images[i]).c_str());
	}
	/************************************************************************************************************************************/

	Buttons.resize(S_TOTAL);
	/********************************************Other buttons like back and arrows******************************************************/
	Buttons[S_Selecting].push_back(new ButtonUI("LevelLeft"
		, "Image//arrow.tga", "Image//arrow_hover.tga"
		, levelLayout->GetSizeX() * 0.07, levelLayout->GetSizeX() * 0.07
		, levelLayout->GetPos().x - levelLayout->GetSizeX() / 2.2, levelLayout->GetPos().y
		, 0.6, false
		, 180));

	Buttons[S_Selecting].push_back(new ButtonUI("LevelRight"
		, "Image//arrow.tga", "Image//arrow_hover.tga"
		, levelLayout->GetSizeX() * 0.07, levelLayout->GetSizeX() * 0.07
		, levelLayout->GetPos().x + levelLayout->GetSizeX() / 2.2, levelLayout->GetPos().y
		, 0.6, false));

	Buttons[S_Selecting].push_back(new ButtonUI("AvatarLeft"
		, "Image//arrow.tga", "Image//arrow_hover.tga"
		, AvatarLayout->GetSizeX() * 0.1, AvatarLayout->GetSizeX() * 0.1
		, AvatarLayout->GetPos().x - AvatarLayout->GetSizeX() / 5.7, AvatarLayout->GetPos().y - AvatarLayout->GetSizeY() * 0.24
		, 0.6, false
		, 180));

	Buttons[S_Selecting].push_back(new ButtonUI("AvatarRight"
		, "Image//arrow.tga", "Image//arrow_hover.tga"
		, AvatarLayout->GetSizeX() * 0.1, AvatarLayout->GetSizeX() * 0.1
		, AvatarLayout->GetPos().x + AvatarLayout->GetSizeX() / 5.7, AvatarLayout->GetPos().y - AvatarLayout->GetSizeY() * 0.24
		, 0.6, false));

	Buttons[S_Selecting].push_back(new ButtonUI("Back"
		, "Image//back.tga", "Image//back_hover.tga"
		, m_window_width * 0.05, m_window_width* 0.05
		, m_window_width * 0.035, m_window_width * 0.035
		, 0.6, false));

	Buttons[S_Selected].push_back(new ButtonUI("Yes"
		, "Image//go.tga", "Image//go_hover.tga"
		, selectedLayout->GetSizeX() * 0.2f, selectedLayout->GetSizeX() * 0.2f
		, selectedLayout->GetPos().x - selectedLayout->GetSizeX() * 0.2f, selectedLayout->GetPos().y - selectedLayout->GetSizeY() * 0.2f
		, 0.6, false));

	Buttons[S_Selected].push_back(new ButtonUI("No"
		, "Image//stop.tga", "Image//stop_hover.tga"
		, selectedLayout->GetSizeX() * 0.2f, selectedLayout->GetSizeX() * 0.2f
		, selectedLayout->GetPos().x + selectedLayout->GetSizeX() * 0.2f, selectedLayout->GetPos().y - selectedLayout->GetSizeY() * 0.2f
		, 0.6, false));
	/************************************************************************************************************************************/

	transition = new Layout("", m_window_width, m_window_height, m_window_width * 0.5f, m_window_height * 0.5f, true);
}

void CLevelSelectScene::Update(double dt)
{
	CSceneManager2D::Update(dt);
}

void CLevelSelectScene::Render()
{
	CSceneManager2D::Render();
	
	std::string texts;
	float textsSize;

	modelStack.PushMatrix();
	RenderMeshIn2D(meshList[GEO_BG], false);
	modelStack.PopMatrix();

	switch (curentState)
	{
	case S_Selecting:
		levelLayout->render(this, 2);
		AvatarLayout->render(this, 2);

		texts = "Select Level";
		textsSize = levelLayout->GetSizeY() * 0.13f;
		RenderTextOnScreen(meshList[GEO_TEXT], texts, Color(1, 1, 1), textsSize, levelLayout->GetPos().x - (textsSize * 0.5 * texts.size() * 0.5), levelLayout->GetPos().y - textsSize * 0.5 + levelLayout->GetSizeY() * 0.39f, 3);

		texts = "Select Avatar";
		textsSize = AvatarLayout->GetSizeY() * 0.09f;
		RenderTextOnScreen(meshList[GEO_TEXT], texts, Color(0, 0, 0), textsSize, AvatarLayout->GetPos().x - (textsSize * 0.5 * texts.size() * 0.5), AvatarLayout->GetPos().y - textsSize * 0.5 + AvatarLayout->GetSizeY() * 0.39f, 3);

		for (unsigned int i = 0; i < Buttons[S_Selecting].size(); i++)
		{
			Buttons[S_Selecting][i]->render(this, meshList[GEO_TEXT], Color(0, 0, 0), 3);
		}

		for (unsigned int i = 0; i < LevelButtons[currentPage].size(); i++)
		{
			LevelButtons[currentPage][i]->render(this, meshList[GEO_TEXT], Color(1, 1, 1), 3);
		}

		RenderMeshIn2D(AvatarImages[currentAvatarImage], false, 1, 1, AvatarLayout->GetPos().x, AvatarLayout->GetPos().y, 3, 0, -AvatarLayout->GetSizeX() * 0.4f * 0.5f);
		break;

	case S_Selected:
		selectedLayout->render(this, 4);

		texts = "Start Level " + selectedLevelName + "?";
		textsSize = selectedLayout->GetSizeY() * 0.15f;
		RenderTextOnScreen(meshList[GEO_TEXT], texts, Color(0, 0, 0), textsSize, selectedLayout->GetPos().x - (textsSize * 0.5 * texts.size() * 0.5), selectedLayout->GetPos().y - textsSize * 0.5 + selectedLayout->GetSizeY() * 0.2f, 5);

		for (unsigned int i = 0; i < Buttons[S_Selected].size(); i++)
		{
			Buttons[S_Selected][i]->render(this, meshList[GEO_TEXT], Color(0, 0, 0), 5);
		}

		break;
	}

	transition->render(this, 6);
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