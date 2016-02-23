#pragma once

#include "GameState.h"
#include "../Scenes/OptionsScene.h"

class OptionsState : public CGameState
{
public:
	void Init();
	void Init(const int width, const int height);
	void Cleanup();

	void Pause();
	void Resume();
	
	void Update(CGameStateManager* theGSM);
	void Update(CGameStateManager* theGSM, const double m_dElasedTime);
	void Draw(CGameStateManager* theGSM);

	static OptionsState* Instance(){
		return &theOptionsState;
	}

protected:
	OptionsState() {}
private:
	static OptionsState theOptionsState;

	OptionsScene *scene;

};