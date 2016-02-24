#include "Timer.h"


Timer::Timer()
{
	duration = 3.0f;
	dur_Copy = duration;
}

Timer::Timer(float countdown)
{
	this->duration = countdown;

	dur_Copy = countdown;
}
Timer::~Timer()
{
}

float Timer::GetDuration()
{
	return duration;
}
void Timer::SetDuration(float duration)
{
	this->duration = duration;
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
	if (active)
	{
		duration -= dt;
		if (duration <= 0)
		{
			duration = dur_Copy;
			active = false;
			return true;
		}
	}
	return false;
}
