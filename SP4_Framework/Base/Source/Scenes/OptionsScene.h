#include "SceneManager2D.h"
#include "../UI/SliderUI.h"
#include "../FileReading.h"
#include "../Luala.h"
#include "../UI/ButtonUI.h"
#include"../UI/Layout.h"
#include"../Cursor/Cursor.h"

class OptionsScene : public CSceneManager2D
{
public:

	enum GEOMETRY_TYPE
	{
		GEO_SPLASH,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

	OptionsScene();
	OptionsScene(int m_window_width, int m_window_height);
	~OptionsScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	std::vector<SliderUI*> Sliders;

	std::vector<ButtonUI*>& getButtons() { return Buttons; }

	Layout *transition;
private:
	Mesh* meshList[NUM_GEOMETRY];
	FileReading* Fr;
	float volume1;
	float volume2;
	bool soundPlaying;

	Cursor * cursor;

	std::vector<ButtonUI*> Buttons;
};