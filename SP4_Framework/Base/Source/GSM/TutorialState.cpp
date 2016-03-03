#include <iostream>
using namespace std;

#include "TutorialState.h"
#include "GameStateManager.h"
#include "MenuState.h"

CTutorialState CTutorialState::theGameplayState;

void CTutorialState::Init()
{
	scene = new CTutorialScene(800, 600);
	scene->Init();
}

void CTutorialState::Init(const int width, const int height)
{
	scene = new CTutorialScene(width, height);
	scene->Init();
}

void CTutorialState::Cleanup()
{
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CTutorialState::Pause()
{
}

void CTutorialState::Resume()
{
}

void CTutorialState::HandleEvents(CGameStateManager* theGSM)
{
}

void CTutorialState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void CTutorialState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
}

void CTutorialState::Update(CGameStateManager* theGSM)
{
	scene->Update(0.16667);
}

void CTutorialState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);

	if (scene->getGameState() == scene->GameStates::EXIT)
		mode = 1;
	//if (scene->getTutState() == scene->TutStates::CLEAR && !scene->getWin())
		//mode = 1;
	
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
			theGSM->ChangeState(CMenuState::Instance());
			break;
		}
		mode = -1;
	}
}

void CTutorialState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}
