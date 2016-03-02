#include "SoundManager.h"

using namespace irrklang;

//Sound manager constructor
SoundManager::SoundManager()
: SE(NULL)
{
	SE = createIrrKlangDevice();
}

//Sound manager destructor
SoundManager::~SoundManager()
{
}

//Sound manager init
void SoundManager::Init()
{
	//SE = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
}

//to update sound manager.
void SoundManager::Update()
{

}

void SoundManager::Play(std::string filepath, bool loopit)
{
	SE->play2D(filepath.c_str(), loopit, false);
}

void SoundManager::Play(std::string filepath, bool loopit, bool Startpause)
{
	SE->play2D(filepath.c_str(), loopit, Startpause);
}

void SoundManager::SetSoundVol(float value)
{
	SE->setSoundVolume(value);
}

float SoundManager::GetSoundVol()
{
	return SE->getSoundVolume();
}

void SoundManager::StopSounds()
{
	SE->stopAllSounds();
}

void SoundManager::Exit()
{
	if (SE)
	{
		SE->drop();
		SE = NULL;
	}

}