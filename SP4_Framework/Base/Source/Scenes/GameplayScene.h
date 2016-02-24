#pragma once
#include "SceneManager2D.h"
#include <vector>
#include "../Level.h"

class CGameplayScene: public CSceneManager2D
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		NUM_GEOMETRY,
	};

	enum States
	{
		S_Play = 0,
		S_Pause,
		S_TOTAL,
	};
	States getCurentStae() { return curentState; }
	void setCurrentState(States s) { curentState = s; }

	CGameplayScene();
	CGameplayScene(int m_window_width, int m_window_height, std::string level, std::string avatar);
	~CGameplayScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	Mesh* meshList[NUM_GEOMETRY];

	States curentState;

	Level gameLevel;
};