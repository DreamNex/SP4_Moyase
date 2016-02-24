#include <iostream>
using namespace std;

#include "LevelSelectState.h"
#include "GameStateManager.h"
#include "MenuState.h"
#include "GameplayState.h"
#include "../Application.h"

CLevelSelectState CLevelSelectState::theLevelSelectState;

void CLevelSelectState::Init()
{
	scene = new CLevelSelectScene(800, 600);
	scene->Init();
}

void CLevelSelectState::Init(const int width, const int height)
{
	scene = new CLevelSelectScene(width, height);
	scene->Init();
}

void CLevelSelectState::Cleanup()
{
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CLevelSelectState::Pause()
{
}

void CLevelSelectState::Resume()
{
}

void CLevelSelectState::HandleEvents(CGameStateManager* theGSM)
{
}

void CLevelSelectState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

bool mousePress = false;

void CLevelSelectState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
	switch (scene->getCurentStae())
	{
		case CLevelSelectScene::S_Selecting:
		{
			for (unsigned int i = 0; i < scene->getLevelButtons()[scene->getCurrentPage()].size(); ++i)
			{
				if (scene->getLevelButtons()[scene->getCurrentPage()][i]->CheckMouseOver((float)mouse_x, (float)mouse_y))
				{
					if (mousePress && button_Left == 0)
					{
						CGameStateManager::selectedLevel = scene->getLevelButtons()[scene->getCurrentPage()][i]->getLevelName();
						CGameStateManager::selectedAvatar = scene->getAvatarImages()[scene->getCurrentAvatarImage()]->name;
						scene->setSelectedLevelName(scene->getLevelButtons()[scene->getCurrentPage()][i]->GetText());
						scene->setCurrentState(CLevelSelectScene::S_Selected);
					}
					break;
				}
			}

			for (unsigned int i = 0; i < scene->getButtons()[CLevelSelectScene::S_Selecting].size(); ++i)
			{
				if (scene->getButtons()[CLevelSelectScene::S_Selecting][i]->CheckMouseOver((float)mouse_x, (float)mouse_y))
				{
					if (mousePress && button_Left == 0)
					{
						if (scene->getButtons()[CLevelSelectScene::S_Selecting][i]->GetText() == "LevelLeft")
						{
							if (scene->getCurrentPage() == 0)
								scene->setCurrentPage(scene->getnumOfPage() - 1);
							else
								scene->setCurrentPage(scene->getCurrentPage() - 1);
						}
						else if (scene->getButtons()[CLevelSelectScene::S_Selecting][i]->GetText() == "LevelRight")
						{
							if (scene->getCurrentPage() == scene->getnumOfPage() - 1)
								scene->setCurrentPage(0);
							else
								scene->setCurrentPage(scene->getCurrentPage() + 1);
						}
						if (scene->getButtons()[CLevelSelectScene::S_Selecting][i]->GetText() == "AvatarLeft")
						{
							if (scene->getCurrentAvatarImage() == 0)
								scene->setCurrentAvatarImage(scene->getTotalAvatarImages() - 1);
							else
								scene->setCurrentAvatarImage(scene->getCurrentAvatarImage() - 1);
						}
						else if (scene->getButtons()[CLevelSelectScene::S_Selecting][i]->GetText() == "AvatarRight")
						{
							if (scene->getCurrentAvatarImage() == scene->getTotalAvatarImages() - 1)
								scene->setCurrentAvatarImage(0);
							else
								scene->setCurrentAvatarImage(scene->getCurrentAvatarImage() + 1);
						}
						else if (scene->getButtons()[CLevelSelectScene::S_Selecting][i]->GetText() == "Back")
						{
							theGSM->ChangeState(CMenuState::Instance());
						}
					}
					break;
				}
			}
		}
		break;
		
		case CLevelSelectScene::S_Selected:
		{
			for (unsigned int i = 0; i < scene->getButtons()[CLevelSelectScene::S_Selected].size(); ++i)
			{
				if (scene->getButtons()[CLevelSelectScene::S_Selected][i]->CheckMouseOver((float)mouse_x, (float)mouse_y))
				{
					if (mousePress && button_Left == 0)
					{
						if (scene->getButtons()[CLevelSelectScene::S_Selected][i]->GetText() == "Yes")
						{
							theGSM->ChangeState(CGameplayState::Instance());
						}
						else if (scene->getButtons()[CLevelSelectScene::S_Selected][i]->GetText() == "No")
						{
							scene->setCurrentState(CLevelSelectScene::S_Selecting);
						}
					}
					break;
				}
			}
		}
		break;
	}

	if (button_Left == 1)
		mousePress = true;
	else
		mousePress = false;
}

void CLevelSelectState::Update(CGameStateManager* theGSM)
{
	scene->Update(0.16667);
}

void CLevelSelectState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);
}

void CLevelSelectState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}
