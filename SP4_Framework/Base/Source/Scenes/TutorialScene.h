#pragma once
#include "SceneManager2D.h"
#include <vector>

#include"../GameObjects/Balls.h"
#include"../GameObjects/Wall.h"
#include"../GameObjects/Spikes.h"
#include"../GameObjects/Cannon.h"
#include"../GameObjects/Boost.h"
#include"../GameObjects/Slow.h"
#include"../GUIManager/GUIManager.h"
#include"../Controls/Controls.h"
#include"../Timer/Timer.h"

class CTutorialScene: public CSceneManager2D
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
		PAUSE,
		START,
		EXIT,
	};
	CTutorialScene();
	CTutorialScene(int m_window_width, int m_window_height);
	~CTutorialScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	std::vector<GameObject*> gameObjects;
private:
	Mesh* meshList[NUM_GEOMETRY];
	GUIManager * m_GUI;
	Controls * ctrs;
	bool m_state;
	GameStates G_States;
};