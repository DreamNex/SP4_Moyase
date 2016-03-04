#include "Wave.h"

Wave::Wave(float normLength)
:normalLength(normLength)
{
}
Wave::Wave()
: normalLength(1)
{
}
Wave::~Wave()
{
}

Vector2 Wave::GetPath(Vector2 start, Vector2 end, float speed)
{
	if (start == end)
		return Vector2(0, 0);
	
	Vector2 up(0, 1);
	return Vector2(speed, sin(up.AngleBetween((start.Normalized()))) * speed);

}