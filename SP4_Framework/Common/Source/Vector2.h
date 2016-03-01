#ifndef VECTOR2_H
#define VECTOR2_H

struct Vector2
{
	float x, y;
	Vector2( float a = 0, float b = 0 ); //default constructor
	Vector2( const Vector2 &rhs ); //copy constructor
	void Set( float a, float b ); //Set all data
	void SetZero(void);
	Vector2 unary(void)const;
	bool IsZero(void)const;
	Vector2 operator+( const Vector2& rhs ) const; //Vector addition
	Vector2 operator-( const Vector2& rhs ) const; //Vector subtraction
	Vector2 operator-( void ) const; //Unary negation
	Vector2 operator*( float scalar ) const; //Scalar multiplication
	Vector2 operator/ (float scalar) const;
	bool operator==(const Vector2& rhs)const;
	bool operator!=(const Vector2& rhs)const;
	float Length( void ) const; //Get magnitude
	float LengthSquared(void)const;//Get Magnitude Squared
	float Determinant(const Vector2& rhs)const;
	float Dot( const Vector2& rhs ) const; //Dot product
	float AngleBetween(const Vector2& rhs) const; //Angle Between
	Vector2 Normalized(void)const; //Return a copy of this vector, normalized

	float component(Vector2 v, Vector2 dV);
	void componentVector(Vector2 v, Vector2 dV);
	void rotateVector(float angle);
	void RotateClockwise();
	void RotateAntiClockwise();
};
#endif
