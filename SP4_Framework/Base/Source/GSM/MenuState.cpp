#include <iostream>
using namespace std;

#include "MenuState.h"
#include "GameStateManager.h"
#include "LevelSelectState.h"
#include "TutorialState.h"
#include "OptionsState.h"
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
	for (unsigned int i = 0; i < scene->Buttons.size(); ++i)
	{
		scene->Buttons[i]->CheckMouseOver((float)mouse_x, (float)mouse_y);

		if (scene->Buttons[i]->GetText() == "Start" && scene->Buttons[i]->GetMouseover() && button_Left == 1)
		{
			theGSM->ChangeState(CLevelSelectState::Instance());
			break;
		}
		else if (scene->Buttons[i]->GetText() == "How 2 Play" && scene->Buttons[i]->GetMouseover() && button_Left == 1)
		{
			theGSM->ChangeState(CTutorialState::Instance());
			break;
		}
		else if (scene->Buttons[i]->GetText() == "Options" && scene->Buttons[i]->GetMouseover() && button_Left == 1)
		{
			theGSM->ChangeState(OptionsState::Instance());
			break;
		}
		else if (scene->Buttons[i]->GetText() == "Exit" && scene->Buttons[i]->GetMouseover() && button_Left == 1)
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
