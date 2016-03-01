#pragma once
#include "SceneManager2D.h"
#include <vector>
#include "../Level.h"

#include"../GUIManager/GUIManager.h"
#include"../Controls/Controls.h"
#include"../Timer/Timer.h"
#include "../UI/ButtonUI.h"

class CGameplayScene: public CSceneManager2D
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		GEO_BG,
		NUM_GEOMETRY,
	};

	enum GameStates
	{
		S_RESET = 0,
		S_STARTED,
		S_EXIT,
		S_WIN,
		S_TOTAL,
	};
	GameStates getCurentStae() { return curentState; }
	void setCurrentState(GameStates s) { curentState = s; }

	CGameplayScene();
	CGameplayScene(int m_window_width, int m_window_height, std::string level, std::string avatar);
	~CGameplayScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	std::vector<ButtonUI*>* getButtons() { return &Buttons; }
	Layout *transition;

private:
	Mesh* meshList[NUM_GEOMETRY];

	GUIManager * m_GUI;
	Controls * ctrs;
	bool mL_state, mR_state;

	GameStates curentState;

	Level gameLevel;

	//win state stuff
	Layout* winStateOpacity, *resultLayout;
	std::vector<ButtonUI*> Buttons;
};