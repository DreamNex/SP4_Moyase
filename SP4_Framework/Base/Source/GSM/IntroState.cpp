#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "menustate.h"
#include "introstate.h"

CIntroState CIntroState::theIntroState;

void CIntroState::Init()
{
	scene = new CSceneManager2D_Intro(800, 600);
	scene->Init();

	timepass = 0;
}

void CIntroState::Init(const int width, const int height)
{
	scene = new CSceneManager2D_Intro(width, height);
	scene->Init();

	timepass = 0;
}

void CIntroState::Cleanup()
{
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CIntroState::Pause()
{
}

void CIntroState::Resume()
{
}

void CIntroState::HandleEvents(CGameStateManager* theGSM)
{
}

void CIntroState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void CIntroState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							   const int button_Left, const int button_Middle, const int button_Right)
{
}

void CIntroState::Update(CGameStateManager* theGSM) 
{
	scene->Update(0.16667);
}

void CIntroState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	scene->Update(m_dElapsedTime);

	timepass += (float)m_dElapsedTime;
	if (timepass > 2)
	{
		theGSM->ChangeState(CMenuState::Instance());
	}
}

void CIntroState::Draw(CGameStateManager* theGSM) 
{
	scene->Render();
}
