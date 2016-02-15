#include <iostream>
using namespace std;

#include "GameplayState.h"
#include "GameStateManager.h"
#include "MenuState.h"

CGameplayState CGameplayState::theGameplayState;

void CGameplayState::Init()
{
	scene = new CGameplayScene(800, 600);
	scene->Init();
}

void CGameplayState::Init(const int width, const int height)
{
	scene = new CGameplayScene(width, height);
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
	if (scene->getCurentStae() == CGameplayScene::S_Pause)
	{
		for (int i = 0; i < scene->clickTexts.size(); ++i)
		{
			scene->clickTexts[i]->CheckMouseOver(mouse_x, mouse_y);

			if (scene->clickTexts[i]->GetName() == "Resume" && scene->clickTexts[i]->GetMouseover() && button_Left == 1)
			{
				scene->setCurrentState(CGameplayScene::S_Play);
				break;
			}
			if (scene->clickTexts[i]->GetName() == "Quit" && scene->clickTexts[i]->GetMouseover() && button_Left == 1)
			{
				theGSM->ChangeState(CMenuState::Instance());
				break;
			}
		}
	}
}

void CGameplayState::Update(CGameStateManager* theGSM)
{
	scene->Update(0.16667);
}

void CGameplayState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);
}

void CGameplayState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}
