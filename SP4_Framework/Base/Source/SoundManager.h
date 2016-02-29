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
	void Exit();

	//Play a 2D sound
	//Loopit makes it loop thru the sound file
	void Play(std::string filepath, bool loopit = false);

	//Overloaded sound
	//Pause is to be able to edit the sound using irrklang functions
	void Play(std::string filepath, bool loopit = false, bool pause = false);
};
#endif