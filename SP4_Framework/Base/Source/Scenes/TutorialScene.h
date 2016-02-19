#pragma once
#include "SceneManager2D.h"
#include <vector>

#include"../GameObjects/Balls.h"
#include"../GameObjects/Wall.h"
#include"../GameObjects/Spikes.h"

class CTutorialScene: public CSceneManager2D
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		NUM_GEOMETRY,
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
};