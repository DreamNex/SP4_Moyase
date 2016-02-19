#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H
#include <string>
#include "irrKlang.h"

using namespace irrklang;

class SoundManager
{

public:
	SoundManager();
	~SoundManager();

	void Init();
	void Update();

	//Play a 2D sound
	void Play(std::string filepath, bool loopit = false);

	//sound engine
	ISoundEngine* SE;
};
#endif