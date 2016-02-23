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

bool mousePress = false;

void CLevelSelectState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right)
{
	for (unsigned int i = 0; i < scene->getButtons().size(); ++i)
	{
		if (scene->getButtons()[i]->CheckMouseOver((float)mouse_x, (float)mouse_y))
		{
			if (mousePress && button_Left == 0)
			{
				if (scene->getButtons()[i]->GetText() == "LevelLeft")
				{
					if (scene->getCurrentPage() == 0)
						scene->setCurrentPage(scene->getnumOfPage() - 1);
					else
						scene->setCurrentPage(scene->getCurrentPage() - 1);
				}
				else if (scene->getButtons()[i]->GetText() == "LevelRight")
				{
					if (scene->getCurrentPage() == scene->getnumOfPage() - 1)
						scene->setCurrentPage(0);
					else
						scene->setCurrentPage(scene->getCurrentPage() + 1);
				}
			}
			break;
		}
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
