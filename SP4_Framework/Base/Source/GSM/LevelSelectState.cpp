#include <iostream>
using namespace std;

#include "LevelSelectState.h"
#include "GameStateManager.h"
//#include "MenuState.h"
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

void CLevelSelectState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
	/*
	for (unsigned int i = 0; i < scene->Buttons.size(); ++i)
	{
		scene->Buttons[i]->CheckMouseOver((float)mouse_x, (float)mouse_y);

		if (scene->Buttons[i]->GetText() == "Start" && scene->Buttons[i]->GetMouseover() && button_Left == 1)
		{
			theGSM->ChangeState(CGameplayState::Instance());
			break;
		}
		else if (scene->Buttons[i]->GetText() == "How 2 Play" && scene->Buttons[i]->GetMouseover() && button_Left == 1)
		{
			theGSM->ChangeState(CTutorialState::Instance());
			break;
		}
		else if (scene->Buttons[i]->GetText() == "Exit" && scene->Buttons[i]->GetMouseover() && button_Left == 1)
		{
			Application::exitbool = true;
			break;
		}
	}
	*/
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
