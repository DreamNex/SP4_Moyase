#pragma once
#include "SceneManager2D.h"
#include <vector>

#include"../GameObjects/Balls.h"
#include"../GameObjects/Wall.h"
#include"../GameObjects/Spikes.h"
#include"../GameObjects/Cannon.h"
#include"../GameObjects/Boost.h"
#include"../GameObjects/Slow.h"
#include"../Controls/Controls.h"
#include"../Timer/Timer.h"
#include"../Aesthetics/Particles/ParticleManager.h"
#include"../GameObjects/Exit.h"

class CTutorialScene: public CSceneManager2D
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		GEO_BG,
		GEO_TEST,
		GEO_MO,
		GEO_PLAY,
		GEO_RESET,
		GEO_GUI1,
		GEO_DRAG,
		GEO_ROT,
		GEO_WIN,
		NUM_GEOMETRY,
	};
	enum GameStates
	{
		RESET,
		START,
		EXIT,
		WIN,
		NUM_STATES,
	};
	enum TutStates
	{
		MOver,
		PLAY,
		RPLAY,
		RPLAY2,
		RPLAY3,
		GUI,
		TRESET,
		DRAGHERE,
		ROTATE,
		CLEAR,
		NUM_TSTATES,
	};
	CTutorialScene();
	CTutorialScene(int m_window_width, int m_window_height);
	~CTutorialScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void vExit();

	std::vector<GameObject*> gameObjects;

	GameStates getGameState() { return G_States; }
	TutStates getTutState() { return T_States; }
	bool getWin() { return win; }

	Layout *transition;
private:
	Mesh* meshList[NUM_GEOMETRY];
	GUIManager * m_GUI;
	Controls * ctrs;
	//bool mL_state, mR_state;
	GameStates G_States;
	TutStates T_States;
	Cursor *cursor;

	Balls* getBall;
	Timer* trail;

	//tutorial render bools
	bool MO;
	bool play;
	bool rplay;
	bool vreset;
	bool gui;
	bool drag;
	bool rotate;
	bool win;
	bool onClick;
};