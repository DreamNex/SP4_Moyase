#include <iostream>
using namespace std;

#include "../Application.h"
#include "GameStateManager.h"
#include "OptionsState.h"
#include "MenuState.h"

OptionsState OptionsState::theOptionsState;

void OptionsState::Init()
{
	playonce = false;
	scene = new OptionsScene(800, 600);
	scene->Init();
}

void OptionsState::Init(const int width, const int height)
{
	playonce = false;
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
	for (unsigned int i = 0; i < scene->getButtons().size(); ++i)
	{
		if (scene->getButtons()[i]->CheckMouseOver((float)mouse_x, (float)mouse_y))
		{
			if (!playonce)
			{
				Application::SFX.Play("SoundTracks//HoverTrack.mp3", false, false);
				playonce = true;
			}
			if (mousePress && button_Left == 0)
			{
				Application::SFX.Play("SoundTracks//ClickTrack.mp3", false, false);
				mode = 1;
			}
			break;
		}

		if (i + 1 == scene->getButtons().size())
		{
			playonce = false;
		}
	}

	if (button_Left == 1)
		mousePress = true;
	else
		mousePress = false;
}

void OptionsState::Update(CGameStateManager* theGSM)
{
	scene->Update(0.16667);
}

void OptionsState::Update(CGameStateManager* theGSM, const double m_dElaspedTime)
{
	scene->Update(m_dElaspedTime);

	if (mode != -1)
		scene->transition->goOpaque(m_dElaspedTime, 140);
	else if (scene->transition->getTransparent() < 100)
	{
		scene->transition->goTransparent(m_dElaspedTime, 140);
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

void OptionsState::Draw(CGameStateManager* theGSM)
{
	scene->Render();
}