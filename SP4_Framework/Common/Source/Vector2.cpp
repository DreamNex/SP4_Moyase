#include "Vector2.h"
#include <math.h>
#include <cmath>
#include "MyMath.h"

/*
ADDDD ALL TEEH MATTHHH STUFFFFF!!!
ADDD ALL TEEH MATTHHH STUFFFFF!!!ADDD ALL TEEH MATTHHH STUFFFFF!!!
*/

Vector2::Vector2( float a, float b )
{
	x = a;
	y = b;
}

Vector2::Vector2( const Vector2 &rhs )
{
	x = rhs.x;
	y = rhs.y;
}

void Vector2::Set( float a, float b )
{
	x = a;
	y = b;
}

void Vector2::SetZero(void)
{
	x = 0;
	y = 0;
}

bool Vector2::IsZero(void)const
{
	return (x == 0 && y == 0);
}

Vector2 Vector2::operator+( const Vector2& rhs ) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-( const Vector2& rhs ) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator-( void ) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*( float scalar ) const
{
	return Vector2(scalar * x, scalar * y);
}

Vector2 Vector2::operator / (float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

bool Vector2::operator==(const Vector2& rhs)const
{
	return (x == rhs.x || y == rhs.y);
}

bool Vector2::operator!=(const Vector2& rhs)const
{
	return (x != rhs.x || y != rhs.y);
}

float Vector2::Length( void ) const
{
	return sqrt(x * x + y * y);
}

float Vector2::LengthSquared(void)const
{
	return x * x + y * y;
}

float Vector2::Dot( const Vector2& rhs ) const
{
	return x * rhs.x + y * rhs.y;
}

float Vector2::AngleBetween(const Vector2& rhs)const
{
	float dp = this->Dot(rhs);
	return acos(dp / (this->Length() * rhs.Length()));
}

Vector2 Vector2::Normalized(void)const
{
	return Vector2(-y, +x);
}

float Vector2::component(Vector2 v, Vector2 dV)
{
	float alpha = atan2(dV.y, dV.x);
	float theta = atan2(v.y, v.x);

	float length = v.Length();
	
	return length * cos(theta - alpha);
}

void Vector2::componentVector(Vector2 v, Vector2 dV)
{
	v = dV.Normalized();
	*this = component(v, dV);
}

void Vector2::rotateVector(float angle)
{
	float tempx = this->x;
	float tempy = this->y;
	
	angle = Math::DegreeToRadian(angle);

	this->x = tempx * cos(angle) - tempy * sin(angle);
	this->y = tempx * sin(angle) + tempy * cos(angle);
}