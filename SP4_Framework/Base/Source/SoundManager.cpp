#include "SoundManager.h"

using namespace irrklang;

//Sound manager constructor
SoundManager::SoundManager()
: SE(NULL)
{

}

//Sound manager destructor
SoundManager::~SoundManager()
{
}

//Sound manager init
void SoundManager::Init()
{
	SE = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
}

//to update sound manager.
void SoundManager::Update()
{

}

void SoundManager::Play(std::string filepath, bool loopit)
{
	SE->play2D(filepath.c_str(), loopit, false);
}

void SoundManager::Exit()
{
	SE->drop();
}