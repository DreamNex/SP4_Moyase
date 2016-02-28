#pragma once
#include "SceneManager2D.h"
#include "../UI/SpecialMenuButton.h"
#include <vector>
#include "../Cursor/Cursor.h"

class CSceneManager2D_Menu: public CSceneManager2D
{
public:

	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		GEO_BG,
		NUM_GEOMETRY,
	};

	CSceneManager2D_Menu();
	CSceneManager2D_Menu(int m_window_width, int m_window_height);
	~CSceneManager2D_Menu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	
	std::vector<SpecialMenuButton*> Buttons;
private:
	Mesh* meshList[NUM_GEOMETRY];
	Cursor * cursor;
};