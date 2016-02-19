#include "Timer.h"


Timer::Timer()
{
	countdown = 3.0f;
	countdowncopy = countdown;
}

Timer::Timer(float countdown)
{
	this->countdown = countdown;

	countdowncopy = countdown;
}
Timer::~Timer()
{
}

float Timer::GetTimer()
{
	return countdown;
}
void Timer::SetTimer(float countdown)
{
	this->countdown = countdown;
}


bool Timer::GetActive()
{
	return active;
}
void Timer::Start()
{
	active = true;
}

void Timer::Stop()
{
	active = false;
}

bool Timer::Update(float dt)
{
	if (active == true)
	{
		countdown -= dt;
		if (countdown <= 0)
		{
			countdown = countdowncopy;
			active = false;
			return true;
		}
	}
	else if (active == false)
	{
		return false;
	}
}
