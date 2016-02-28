#include "../Mesh.h"
#include <vector>

struct Animation
{
	Animation(){}

	void Set(int startFrame, int endFrame, int repeat, float time)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->repeatCount = repeat;
		this-> animTime = time;
	}

	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool ended;
};

class SpriteAnimation:public Mesh
{
public:
	SpriteAnimation(const std::string & meshName, int row, int col);
	~SpriteAnimation();
	void Update(double dt);
	virtual void Render();
	
	int SetMax(int x, int y);
	int SetMin(int x, int y);

	int m_row;
	int m_col;

	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation *m_anim;
};