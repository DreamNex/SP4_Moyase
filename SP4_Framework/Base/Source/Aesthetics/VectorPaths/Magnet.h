#ifndef MAGNET_H
#define MAGNET_H

#include "VectorPathing.h"

class Magnet : public VectorPathing
{
public:
	Magnet(bool);
	Magnet();
	~Magnet();

	Vector2 GetPath(Vector2 start, Vector2 end, float speed);
private:
	bool push;
};

#endif