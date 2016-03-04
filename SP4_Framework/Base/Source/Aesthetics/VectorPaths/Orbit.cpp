#include "Orbit.h"


Orbit::Orbit(float normProp, float normLength)
: normalProportion(normProp)
, normalLength(normLength)
{
}

Orbit::Orbit()
: normalProportion(1)
, normalLength(1)
{
}

Orbit::~Orbit()
{
}

Vector2 Orbit::GetPath(Vector2 start, Vector2 end, float speed)
{
	if (start == end)
		return Vector2(0, 0);


	Vector2 norm = (end - start).Normalized();
	norm.RotateClockwise();
	return norm * speed;
	
	/*
	Vector2 up(0, 1);
	Vector2 path = end - start;
	Vector2 normPos = start + (path.Normalized() * (path * normalProportion).Length());
	normPos.rotateVector(-90);
	normPos = normPos + (normPos.Normalized() * normalLength);

	return (normPos - start).Normalized() * speed;
	*/
}