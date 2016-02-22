#include "SoundManager.h"
#include "irrKlang.h"

using namespace irrklang;

//Sound manager constructor
SoundManager::SoundManager()
: SE(NULL)
{

}

//Sound manager destructor
SoundManager::~SoundManager()
{
	if (SE != NULL)
	{
		SE->drop();
	}
}

//Sound manager init
void SoundManager::Init()
{
	//SE = createIrrKlangDevice();
}

//to update sound manager.
void SoundManager::Update()
{

}

void SoundManager::Play(std::string filepath, bool loopit)
{
	//SE->play2D(filepath.c_str(), loopit, true);
}