#pragma once
#include "../GUIManager/GUIManager.h"
#include "../GameObjects/GameObject.h"

class Controls
{
public:
	enum CONTROLS_STATE
	{
		SELECTION,
		PLACEMENT,
		ROTATION
	};

	Controls(GUIManager * m_GUI);
	~Controls();


	//void SetState(Controls::CONTROLS_STATE c_state);

	void OnClick(Vector2 mousePos);
	void OnDrag(Vector2 MOUSEPOS);

private:
	GameObject *SelctedGO;
	std::vector<GameObject*> g_Obj;
	CONTROLS_STATE c_state;
	GUIManager *m_GUI;
	GameObject *GetSelection(Vector2 mousePos);
	bool b_Drag;
	
};

