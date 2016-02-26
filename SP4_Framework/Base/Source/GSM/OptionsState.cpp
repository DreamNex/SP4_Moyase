#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "OptionsState.h"
#include "MenuState.h"

OptionsState OptionsState::theOptionsState;

void OptionsState::Init()
{
	scene = new OptionsScene(800, 600);
	scene->Init();
}

void OptionsState::Init(const int width, const int height)
{
	scene = new OptionsScene(width, height);
	scene->Init();
}

void OptionsState::Cleanup()
{
	scene->Exit();
	delete scene;
	scene = NULL;
}

void OptionsState::Pause()
{
}

void OptionsState::Resume()
{
}

void OptionsState::HandleEvents(CGameStateManager* theGSM)
{
}

void OptionsState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
}

void OptionsState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{
}

void OptionsState::Update(CGameStateManager* theGSM)
{
	scene->Update(0.16667);
}

void OptionsState::Update(CGameStateManager* theGSM, const double m_dElaspedTime)
{
	scene->Update(m_dElaspedTime);
}

void OptionsState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}