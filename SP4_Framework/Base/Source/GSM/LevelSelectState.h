#pragma once

#include "gamestate.h"
#include "../Scenes/LevelSelectScene.h"

class CLevelSelectState : public CGameState
{
public:
	void Init();
	void Init(const int width, const int height);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* theGSM);
	void HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status = true);
	void HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							  const int button_Left, const int button_Middle, const int button_Right);
	void Update(CGameStateManager* theGSM);
	void Update(CGameStateManager* theGSM, const double m_dElapsedTime);
	void Draw(CGameStateManager* theGSM);

	static CLevelSelectState* Instance() {
		return &theLevelSelectState;
	}

protected:
	CLevelSelectState() { }

private:
	static CLevelSelectState theLevelSelectState;

	CLevelSelectScene *scene;

	bool playonce;
	bool playonce2;
	bool playonce3;
};
