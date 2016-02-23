#pragma once
#include "../GUIManager/GUIManager.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Cannon.h"
#include "../GameObjects/Boost.h"
#include "../GameObjects/Slow.h"
#include"../Timer/Timer.h"

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

	void SetLevelAssets(std::vector<GameObject*> levelAssets);
	void OnClick(Vector2 mousePos, bool m_state, float dt);
	void Render(CSceneManager2D *SceneManger2D);

	Timer GetTimer();
	void SetTimer(Timer timer);

private:
	bool SelectedActive;
	GameObject *SelctedGO;
	std::vector<GameObject*> g_Obj;
	std::vector<GameObject*> levelAssets;
	CONTROLS_STATE c_state;
	GUIManager *m_GUI;
	bool GetSelection(Vector2 mousePos);
	bool GetPlacement(Vector2 mousePos);
	Timer click_timer;
	bool enableClick;
};

