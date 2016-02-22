#pragma once
#include "SceneManager2D.h"
#include "../UI/ButtonUI.h"
#include <vector>

class CLevelSelectScene: public CSceneManager2D
{
public:

	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		GEO_BG,
		NUM_GEOMETRY,
	};

	CLevelSelectScene();
	CLevelSelectScene(int m_window_width, int m_window_height);
	~CLevelSelectScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	
	std::vector<ButtonUI*> Buttons;
private:
	Mesh* meshList[NUM_GEOMETRY];
};