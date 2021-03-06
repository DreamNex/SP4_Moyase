#pragma once
#include "SceneManager2D.h"
#include "../UI/LevelButton.h"
#include "../UI/Layout.h"
#include "../FileReading.h"
#include <vector>
#include "../Cursor/Cursor.h"

class CLevelSelectScene: public CSceneManager2D
{
public:

	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		GEO_BG,
		NUM_GEOMETRY,
	};

	enum States
	{
		S_Selecting = 0,
		S_Selected,
		S_TOTAL,
	};
	States getCurentStae() { return curentState; }
	void setCurrentState(States s) { curentState = s; }

	CLevelSelectScene();
	CLevelSelectScene(int m_window_width, int m_window_height);
	~CLevelSelectScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	//function for general buttons
	std::vector<std::vector<ButtonUI*>>& getButtons() { return Buttons; }

	//functions for level buttons
	int getCurrentPage() { return currentPage; }
	void setCurrentPage(int i) { currentPage = i; }
	int getnumOfPage() { return numOfPage; }
	std::vector<std::vector<LevelButton*>>& getLevelButtons() { return LevelButtons; }

	int getCurrentAvatarImage() { return currentAvatarImage; }
	void setCurrentAvatarImage(int i) { currentAvatarImage = i; }
	int getTotalAvatarImages() { return totalAvatarImages; }
	std::vector<Mesh*>& getAvatarImages() { return AvatarImages; };

	void setSelectedLevelName(std::string s) { selectedLevelName = s; }

	Layout *transition;
private:
	States curentState;

	Mesh* meshList[NUM_GEOMETRY];

	Layout *levelLayout, *AvatarLayout, *selectedLayout;
	
	//vector of vector of Buttons, 1st vector to detemine the state of game
	std::vector<std::vector<ButtonUI*>> Buttons;
	
	//for the level selection
	int currentPage;
	int numOfPage;
	std::vector<std::vector<LevelButton*>> LevelButtons;

	int currentAvatarImage;
	int totalAvatarImages;
	std::vector<Mesh*> AvatarImages;

	std::string selectedLevelName;

	Cursor * cursor;

	void sortLevelNames(vector<string>* s);
};