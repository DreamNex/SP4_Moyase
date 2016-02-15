#include <iostream>
using namespace std;

#include "menustate.h"
#include "GameStateManager.h"
#include "GameplayState.h"
#include "../Application.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
	scene = new CSceneManager2D_Menu(800, 600);
	scene->Init();
}

void CMenuState::Init(const int width, const int height)
{
	scene = new CSceneManager2D_Menu(width, height);
	scene->Init();
}

void CMenuState::Cleanup()
{
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CMenuState::Pause()
{
}

void CMenuState::Resume()
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
	for (int i = 0; i < scene->clickTexts.size(); ++i)
	{
		scene->clickTexts[i]->CheckMouseOver(mouse_x, mouse_y);

		if (scene->clickTexts[i]->GetName() == "Start" && scene->clickTexts[i]->GetMouseover() && button_Left == 1)
		{
			theGSM->ChangeState(CGameplayState::Instance());
			break;
		}
		if (scene->clickTexts[i]->GetName() == "Exit" && scene->clickTexts[i]->GetMouseover() && button_Left == 1)
		{
			Application::exitbool = true;
			break;
		}
	}
}

void CMenuState::Update(CGameStateManager* theGSM) 
{
	scene->Update(0.16667);
}

void CMenuState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);
}

void CMenuState::Draw(CGameStateManager* theGSM) 
{
	scene->Render();
}
