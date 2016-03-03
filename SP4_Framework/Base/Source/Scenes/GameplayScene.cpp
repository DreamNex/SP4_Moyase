#include "GameplayScene.h"
#include "GL\glew.h"

#include "../shader.hpp"
#include "../MeshBuilder.h"
#include "../Application.h"
#include "../Utility.h"
#include "../LoadTGA.h"
#include "../Luala.h"
#include <sstream>

CGameplayScene::CGameplayScene()
:
gameLevel("", "")
{
}

CGameplayScene::CGameplayScene(int m_window_width, int m_window_height, std::string level, std::string avatar)
:
CSceneManager2D(m_window_width, m_window_height)
, gameLevel(level, avatar)

{
	levelName = level;
}

CGameplayScene::~CGameplayScene()
{
	if (m_GUI)
		delete m_GUI;
	
	if (ctrs)
		delete ctrs;

	if (winStateOpacity)
		delete winStateOpacity;
	
	if (resultLayout)
		delete resultLayout;

	if (baseScoreBar)
		delete baseScoreBar;

	if (progressScoreBar)
		delete progressScoreBar;

	for (int i = 0; i < Buttons.size(); ++i)
	{
		if (Buttons[i])
			delete Buttons[i];
	}
}

void CGameplayScene::Init()
{
	CSceneManager2D::Init();

	curentState = S_RESET;

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[GEO_BG] = MeshBuilder::Generate2DMesh("GameBG", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_BG]->textureID = LoadTGA("Image//Tits//GameBG.tga");

	meshList[GEO_SCORE_INDICATOR1] = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	meshList[GEO_SCORE_INDICATOR1]->textureID = LoadTGA("Image//highscore_indicator_1.tga");
	meshList[GEO_SCORE_INDICATOR2] = MeshBuilder::Generate2DMesh("", Color(1, 1, 1), 0, 0, 1, 1);
	meshList[GEO_SCORE_INDICATOR2]->textureID = LoadTGA("Image//highscore_indicator_2.tga");

	meshList[GEO_SCROLLINGBG] = MeshBuilder::Generate2DMesh("GameBG", Color(1, 1, 1), 0, 0, m_window_width, m_window_height);
	meshList[GEO_SCROLLINGBG]->textureID = LoadTGA("Image//scrolling.tga");

	m_GUI = new GUIManager(gameLevel.getToolsArray()[0], gameLevel.getToolsArray()[1], gameLevel.getToolsArray()[2]);
	ctrs = new Controls(m_GUI);

	play_state = false;
	
	transition = new Layout("", m_window_width, m_window_height, m_window_width * 0.5f, m_window_height * 0.5f, true);

	Application::BGM.StopSounds();
	Application::isPlaying = false;

	Application::BGM.Play("SoundTracks//GameplayTrack.mp3", true, false);

	//win state stuff
	winStateOpacity = new Layout("", m_window_width, m_window_height, m_window_width * 0.5f, m_window_height * 0.5f, true, 100);
	resultLayout = new Layout("Image//i_pod.tga", m_window_width * 0.35f, m_window_height * 0.66f, m_window_width * 0.5f, 0);
	
	baseScoreBar = new Layout("Image//scorebar.tga", resultLayout->GetSizeX() * 0.77, resultLayout->GetSizeY() * 0.05, resultLayout->GetPos().x, resultLayout->GetPos().y);
	progressScoreBar = new Layout("Image//score.tga", 0, resultLayout->GetSizeY() * 0.05, resultLayout->GetPos().x, resultLayout->GetPos().y);

	Buttons.push_back(new ButtonUI("back"
		, "Image//back.tga", "Image//back_hover.tga"
		, resultLayout->GetSizeX() * 0.1, resultLayout->GetSizeX() * 0.1
		, resultLayout->GetPos().x - resultLayout->GetSizeX() / 5.7, resultLayout->GetPos().y - resultLayout->GetSizeY() * 0.24
		, 0.6, false));
	Buttons.push_back(new ButtonUI("replay"
		, "Image//replay.tga", "Image//replay_hover.tga"
		, resultLayout->GetSizeX() * 0.1, resultLayout->GetSizeX() * 0.1
		, resultLayout->GetPos().x, resultLayout->GetPos().y - resultLayout->GetSizeY() * 0.24
		, 0.6, false));
	Buttons.push_back(new ButtonUI("nextLv"
		, "Image//arrow.tga", "Image//arrow_hover.tga"
		, resultLayout->GetSizeX() * 0.1, resultLayout->GetSizeX() * 0.1
		, resultLayout->GetPos().x + resultLayout->GetSizeX() / 5.7, resultLayout->GetPos().y - resultLayout->GetSizeY() * 0.24
		, 0.6, false));

	textAlpha = 0;

	showLevel = true;

	scrollingBGpos[0].Set(0, 0);
	scrollingBGpos[1].Set(m_window_width, 0);
}

void CGameplayScene::Update(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (play_state)
		{ 
			ctrs->PlayPause();
			play_state = false;
		}
	}
	else
		play_state = true;
	if (curentState != S_WIN)
		curentState = static_cast<GameStates>(ctrs->GetState());

	mL_state = mR_state = false;
	bool playPause = false;
	if (Application::Button_Left)
		mL_state = true;
	if (Application::Button_Right)
		mR_state = true;

	switch (curentState)
	{
	case S_RESET:
		gameLevel.SetScore(0);
		gameLevel.GetParticleManager()->Clear();
		gameLevel.getBall()->reset();
		gameLevel.update(dt, true);
		m_GUI->Update(dt);
		m_GUI->UpdateScore(gameLevel.GetScore());
		ctrs->Update(this, gameLevel.getGameObjects(), mL_state, mR_state, dt);
		break;

	case S_STARTED:
		m_GUI->Update(dt);
		m_GUI->UpdateScore(gameLevel.GetScore());
		ctrs->Update(this, gameLevel.getGameObjects(), mL_state, mR_state, dt, true);
		curentState = static_cast<GameStates>(gameLevel.update(dt));
		if (curentState == S_RESET || playPause)
		{
			ctrs->SetState(0);
		}
		else if (curentState == S_WIN)
		{
			FileReading FileReader;

			string score4lv;

			/////////////////////////set highscore///////////////////////////////////////
			score4lv = FileReader.GetVariable("Levels//" + levelName, "highscore");
			if (score4lv == "")
				score4lv = "0";
			else if (stoi(score4lv) < 0 || stoi(score4lv) > 5)
				score4lv = "0";
			int i = gameLevel.GetMode();
			if (gameLevel.GetMode() > stoi(score4lv))
				FileReader.SetFloatVal("Levels//" + levelName, "highscore", gameLevel.GetMode());
			/////////////////////////////////////////////////////////////////////////////
			
			/////////////////////////////unlock next level///////////////////////////////
			std::vector<string> levelNames = FileReader.SearchFolder("Levels//", "*.txt");
			sortLevelNames(&levelNames);

			for (int i = 0; i < levelNames.size(); ++i)
			{
				if (levelNames[i] == CGameStateManager::selectedLevel)
				{
					if (i + 1 != levelNames.size())
					{
						FileReader.changeUnlock("Levels//" + levelNames[i + 1]);
					}
					break;
				}
			}
		////////////////////////////////////////////////////////////////////////////
			Application::BGM.StopSounds();
			Application::SFX.StopSounds();
			Application::BGM.Play("SoundTracks//endgame.wav", false, false);
		}
		break;

	case S_WIN:
		gameLevel.update(dt, false, false);
		winScreenUpdae(dt);
		ctrs->Update(this, gameLevel.getGameObjects(), mL_state, mR_state, dt, true);
		break;
	}

	if (showLevel)
	{
		if (textAlpha < 100)
			textAlpha += dt * 20;
		else
		{
			textAlpha = 100;
			showLevel = false;
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		scrollingBGpos[i].x -= dt * 50;
		if (scrollingBGpos[i].x <= -(m_window_width))
			scrollingBGpos[i].x = m_window_width;
	}
}

void CGameplayScene::Render()
{
	CSceneManager2D::Render();

	RenderMeshIn2D(meshList[GEO_BG], false, 1, 1, 0, 0, -2);
	
	for (int i = 0; i < 2; ++i)
	{
		RenderMeshIn2DTrans(meshList[GEO_SCROLLINGBG], 60, 1, 1, scrollingBGpos[i].x, scrollingBGpos[i].y, -1);
	}

	gameLevel.render(this);

	m_GUI->Render(this);

	ctrs->Render(this);

	if (showLevel)
		RenderTextOnScreenTrans(meshList[GEO_TEXT], "Level " + levelName.substr(0, levelName.length() - 4), Color(1, 1, 1), (int)textAlpha, m_window_height * 0.1, 20, m_window_height - m_window_height * 0.1);
	
	switch (curentState)
	{
	case S_WIN:
		winScreenRender();
		break;
	}

	transition->render(this, 10);
}

void CGameplayScene::Exit()
{
	Application::BGM.StopSounds();
	Application::SFX.StopSounds();

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	CSceneManager2D::Exit();
}

void CGameplayScene::winScreenUpdae(double dt)
{
	if (winStateOpacity->getTransparent() > 20)
		winStateOpacity->goOpaque(dt, 70);
	
	if (resultLayout->GetPos().y < m_window_height * 0.5f)
	{
		resultLayout->SetPos(resultLayout->GetPos().x, resultLayout->GetPos().y + dt * m_window_height * 0.4f);
		for (unsigned int i = 0; i < Buttons.size(); ++i)
		{
			Buttons[i]->SetPos(Buttons[i]->GetX(), resultLayout->GetPos().y - resultLayout->GetSizeY() * 0.24);
		}
		baseScoreBar->SetPos(baseScoreBar->GetPos().x, resultLayout->GetPos().y + resultLayout->GetSizeY() * 0.015);
		progressScoreBar->SetPos(baseScoreBar->GetPos().x, resultLayout->GetPos().y + resultLayout->GetSizeY() * 0.015);

	}
	else
	{
		if (textAlpha > 0)
			textAlpha -= dt * 50;

		float a = (float)gameLevel.GetScore();
		float b = (float)gameLevel.GetMaxScore();
		float c = (float)gameLevel.GetScore() / (float)gameLevel.GetMaxScore();

		float barLength = ((float)gameLevel.GetScore()) / ((float)gameLevel.GetMaxScore()) * baseScoreBar->GetSizeX();
		if (progressScoreBar->GetSizeX() < barLength && progressScoreBar->GetSizeX() <= baseScoreBar->GetSizeX())
		{
			progressScoreBar->setScale(progressScoreBar->GetSizeX() + resultLayout->GetSizeX() * 0.3 * dt, progressScoreBar->GetSizeY());
			if (progressScoreBar->GetSizeX() > barLength)
				progressScoreBar->setScale(barLength, progressScoreBar->GetSizeY());
		}
		else
		{
			int i = 1;
		}
	}

	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		if (Buttons[i]->CheckMouseOver((float)Application::mouse_current_x, (float)Application::mouse_current_y));
	}

}

void CGameplayScene::winScreenRender()
{
	winStateOpacity->render(this, 3);
	resultLayout->render(this, 4);
	baseScoreBar->render(this, 5);
	progressScoreBar->render(this, 6);

	for (unsigned int i = 0; i < Buttons.size(); ++i)
	{
		Buttons[i]->render(this, meshList[GEO_TEXT], Color(0, 0, 0), 5);
	}
	
	float startX = resultLayout->GetPos().x - resultLayout->GetSizeX() * 0.2;
	float dist = resultLayout->GetSizeX() * 0.1;
	
	int score = progressScoreBar->GetSizeX() / (baseScoreBar->GetSizeX() / 5);
	
	for (int i = 0; i < 5; ++i)
	{
		if (i < score)
			RenderMeshIn2D(meshList[GEO_SCORE_INDICATOR2], false, resultLayout->GetSizeX() * 0.1, resultLayout->GetSizeY() * 0.1, startX - resultLayout->GetSizeX() * 0.1 * 0.5 + dist * i, resultLayout->GetPos().y + resultLayout->GetSizeY() * 0.08, 5);
		else
			RenderMeshIn2D(meshList[GEO_SCORE_INDICATOR1], false, resultLayout->GetSizeX() * 0.1, resultLayout->GetSizeY() * 0.1, startX - resultLayout->GetSizeX() * 0.1 * 0.5 + dist * i, resultLayout->GetPos().y + resultLayout->GetSizeY() * 0.08, 5);
	}

	if (resultLayout->GetPos().y >= m_window_height * 0.5f)
	{
		std::string texts;
		float textsSize;

		texts = "Level " + levelName.substr(0, levelName.length() - 4);
		textsSize = resultLayout->GetSizeX() * 0.1f;
		RenderTextOnScreenTrans(meshList[GEO_TEXT], texts, Color(0, 0, 0), (int)textAlpha, textsSize, resultLayout->GetPos().x - (textsSize * 0.5 * texts.size() * 0.5), resultLayout->GetPos().y - textsSize * 0.5 + resultLayout->GetSizeY() * 0.38f);

		texts = "Cleared!";
		textsSize = resultLayout->GetSizeX() * 0.11f;
		RenderTextOnScreenTrans(meshList[GEO_TEXT], texts, Color(0, 0, 0), (int)textAlpha, textsSize, resultLayout->GetPos().x - (textsSize * 0.5 * texts.size() * 0.5), resultLayout->GetPos().y - textsSize * 0.5 + resultLayout->GetSizeY() * 0.28f);

		//texts = "Select Avatar";
		//textsSize = AvatarLayout->GetSizeY() * 0.09f;
		//RenderTextOnScreen(meshList[GEO_TEXT], texts, Color(0, 0, 0), textsSize, AvatarLayout->GetPos().x - (textsSize * 0.5 * texts.size() * 0.5), AvatarLayout->GetPos().y - textsSize * 0.5 + AvatarLayout->GetSizeY() * 0.39f, 3);
	}
}

void CGameplayScene::sortLevelNames(vector<string>* s)
{
	vector<int> tempVec;

	for (int i = 0; i < s->size(); ++i)
	{
		(*s)[i].substr(0, (*s)[i].length() - 4);
		tempVec.push_back(stoi((*s)[i]));
	}

	for (int i = 0; i < tempVec.size(); ++i)
	{
		for (int j = i + 1; j < tempVec.size(); ++j)
		{
			if (tempVec[i] > tempVec[j])
			{
				int abc = tempVec[j];
				tempVec[j] = tempVec[i];
				tempVec[i] = abc;
			}
		}
	}

	s->clear();

	for (int i = 0; i < tempVec.size(); ++i)
	{
		s->push_back(std::to_string(tempVec[i]) + ".txt");
	}
}