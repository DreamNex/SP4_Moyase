#include "Magnet.h"


Magnet::Magnet(bool pushpull)
: push(pushpull)
{
}

Magnet::Magnet()
: push(true)
{
}

Magnet::~Magnet()
{
}

Vector2 Magnet::GetPath(Vector2 start, Vector2 end, float speed)
{
	if (start == end)
		return Vector2(0, 0);
	if (push)
		return ((end - start).Normalized() * speed);

	return ((start - end).Normalized() * speed);
}