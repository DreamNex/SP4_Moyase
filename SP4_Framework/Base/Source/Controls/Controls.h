#pragma once
#include "../GameObjects/Cannon.h"
#include "../GameObjects/Boost.h"
#include "../GameObjects/Slow.h"
#include"../Timer/Timer.h"
#include"../Cursor/Cursor.h"
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

	void Update(CSceneManager2D* sm, std::vector<GameObject*> &levelAssets, bool ml_state, bool mr_state, float dt, bool guiOnly = false);
	void Render(CSceneManager2D *SceneManager2D);

	void GetSelection(Vector2 mousePos);
	void GetSelection(std::vector<GameObject*> &levelAssets, Vector2 mousePos);
	void GetPlacement(std::vector<GameObject*> &levelAssets, Vector2 mousePos);
	void DoRotation(Vector2 mousePos, float dt);
	void SetState(int i);
	int GetState();
	void ResetState();
	void PlayPause();

private:
	CONTROLS_STATE c_state;
	GUIManager *m_GUI;

	//Pointer to the Selected/Created GameObject
	bool SelectedActive;
	int SelectedIndex;
	GameObject *SelectedGO;
	Vector2 oldPos;
	char* key;
	
	//Feedback
	std::vector<Vector2> trajectoryFeedback;
	float anglePrev;
	Mesh* trajPoint;
	Mesh* feedback;
	GameObject* ball;
	bool correct;

	//Cursor
	Vector2 cursorPos;
	Mesh* cursorMesh;
	bool mL_state;
	bool mR_state;
	bool onClicked = false;
	int state;
	std::vector<GameObject*> g_Obj;

	//Cursor Class
	Cursor * cursor;
};

