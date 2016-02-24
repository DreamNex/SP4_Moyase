#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "MenuState.h"
#include "OptionsState.h"

//OptionsState OptionsState::theOptionsState;

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