#pragma once
#include "SceneManager2D.h"
#include "../UI/LevelButton.h"
#include "../UI/Layout.h"
#include "../FileReading.h"
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

	std::vector<ButtonUI*>& getButtons() { return Buttons; }

	int getCurrentPage() { return currentPage; }
	void setCurrentPage(int i) { currentPage = i; }
	int getnumOfPage() { return numOfPage; }
	std::vector<std::vector<LevelButton*>>* getLevelButtons() { return &LevelButtons; }

private:
	Mesh* meshList[NUM_GEOMETRY];

	Layout* mainLayout, *levelLayout;

	FileReading* FileReader;
	
	std::vector<ButtonUI*> Buttons;
	
	//for the level selection
	int currentPage;
	int numOfPage;
	std::vector<std::vector<LevelButton*>> LevelButtons;
};