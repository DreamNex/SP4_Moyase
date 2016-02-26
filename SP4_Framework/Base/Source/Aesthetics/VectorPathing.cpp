#include "VectorPathing.h"


VectorPathing::VectorPathing(int path, Vector2 start, Vector2 end)
{
	this->path = static_cast<VECTOR_PATH>(path);
	this->start = start;
	this->end = end;
}
VectorPathing::VectorPathing()
	: path(REPEL)
	, start(Vector2(0, 0))
	, end(Vector2(0, 0))
{
}
VectorPathing::~VectorPathing()
{
}

void VectorPathing::SetPath(int path, Vector2 start, Vector2 end)
{
	path = static_cast<VECTOR_PATH>(path);
	this->start = start;
	this->end = end;
}
Vector2 VectorPathing::GetPath()
{
	switch (path)
	{
		case ATTRACT:
		{
			return (this->end - this->start).Normalized();
		}
		break;
		case REPEL:
		{
			return (this->start - this->end).Normalized();
		}
		break;
		case ORBIT:
		{
			Vector2 norm = ((this->end - this->start).Normalized());
			norm.rotateVector(90);
			return norm;
		}
		break;
	}
}