#pragma once

#include "ButtonUI.h"

class LevelButton : public ButtonUI
{
public:
	LevelButton(std::string levelName, bool unlock, std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showText, int socre);
	~LevelButton();

	std::string getLevelName() { return levelName; }
	bool getUnlock() { return unlock; }

	void render(CSceneManager2D* SceneManager2D, Mesh* textMesh, Color textCol = Color(0, 0, 0), float z = 0);

private:
	std::string levelName;
	bool unlock;

	Mesh *lockMesh;


	Mesh *HSMesh1, *HSMesh2;
	float hsScaleX, hsScaleY;
	int score;
};