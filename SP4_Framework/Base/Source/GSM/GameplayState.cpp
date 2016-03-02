#include <iostream>
using namespace std;

#include "GameplayState.h"
#include "GameStateManager.h"
#include "LevelSelectState.h"
#include "../FileReading.h"

CGameplayState CGameplayState::theGameplayState;

void CGameplayState::Init()
{
	scene = new CGameplayScene();
	scene->Init();
}

void CGameplayState::Init(const int width, const int height)
{
	scene = new CGameplayScene(width, height, CGameStateManager::selectedLevel, CGameStateManager::selectedAvatar);
	scene->Init();
}

void CGameplayState::Cleanup()
{
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CGameplayState::Pause()
{
}

void CGameplayState::Resume()
{
}

void CGameplayState::HandleEvents(CGameStateManager* theGSM)
{
}

void CGameplayState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void CGameplayState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
	if (scene->getCurentStae() == CGameplayScene::S_WIN)
	{
		for (unsigned int i = 0; i < scene->getButtons()->size(); ++i)
		{
			if (mousePress && button_Left == 0)
			{
				FileReading fr;

				if ((*scene->getButtons())[i]->GetText() == "back" && (*scene->getButtons())[i]->GetMouseover())
				{
					mode = 1;
					break;
				}
				else if ((*scene->getButtons())[i]->GetText() == "replay" && (*scene->getButtons())[i]->GetMouseover())
				{
					mode = 2;
					break;
				}
				else if ((*scene->getButtons())[i]->GetText() == "nextLv" && (*scene->getButtons())[i]->GetMouseover())
				{
					mode = 2;
					std::vector<string> levelNames = fr.SearchFolder("Levels//", "*.txt");
					for (int i = 0; i < levelNames.size(); ++i)
					{
						if (levelNames[i] == CGameStateManager::selectedLevel)
						{
							if (i + 1 == levelNames.size())
							{
								mode = 1;
							}
							else
							{
								CGameStateManager::selectedLevel = levelNames[i + 1];
								mode = 2;
							}
							break;
						}
					}
					break;
				}
			}
		}
	}
	if (scene->getCurentStae() == CGameplayScene::S_EXIT)
	{
		mode = 1;
	}

	if (button_Left == 1)
		mousePress = true;
	else
		mousePress = false;
}

void CGameplayState::Update(CGameStateManager* theGSM)
{
	scene->Update(0.16667);
}

void CGameplayState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);

	if (mode != -1)
		scene->transition->goOpaque(m_dElapsedTime, 140);
	else if (scene->transition->getTransparent() < 100)
	{
		scene->transition->goTransparent(m_dElapsedTime, 140);
	}

	if (scene->transition->getTransparent() == 0)
	{
		switch (mode)
		{
		case 1:
			theGSM->ChangeState(CLevelSelectState::Instance());
			break;
		case 2:
			theGSM->ChangeState(CGameplayState::Instance());
			break;
		}
		mode = -1;
	}
}

void CGameplayState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}
