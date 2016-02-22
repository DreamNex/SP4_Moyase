#pragma once
#include "../ButtonUI.h"
#include <vector>

class GUI :
	public ButtonUI
{

public:
	enum GUITYPEID
	{
		CANNONGUI,
		SLOWGUI,
		BOOSTGUI
	};

	GUI(std::string text, char* normalMesh, char* hoverMesh, float sizeX, float sizeY, float x, float y, float textScaling, bool showTex, GUITYPEID GUITYPEID);
	~GUI();

	int GetType();
	void SetType(int g_typeID);

	bool GetActive();
	void SetActive(bool Active);

private:
	bool BtnIsActive;
	int g_typeID;
};

