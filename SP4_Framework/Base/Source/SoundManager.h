#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H
#include <string>
class SoundManager
{
	SoundManager();
	~SoundManager();

	void Init();
	void Update();

	//Play a 2D sound
	void Play(std::string filepath, bool loopit = false);
};
#endif