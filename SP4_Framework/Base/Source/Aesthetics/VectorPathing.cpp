#include "VectorPathing.h"


VectorPathing::VectorPathing(int path)
{
	this->path = static_cast<VECTOR_PATH>(path);
}
VectorPathing::VectorPathing()
	: path(REPEL)
{
}
VectorPathing::~VectorPathing()
{
}

void VectorPathing::SetPath(int path)
{
	path = static_cast<VECTOR_PATH>(path);
}
Vector2 VectorPathing::GetPath(Vector2 start, Vector2 end)
{
	switch (path)
	{
		case ATTRACT:
		{
			if ((end - start).IsZero())
				return Vector2(0, 0);
			return (end - start).Normalized();
		}
		break;
		case REPEL:
		{
			if ((start - end).IsZero())
				return Vector2(0, 0);
			return (start - end).Normalized();
		}
		break;
		case ORBIT:
		{
			Vector2 norm = (end - start).Normalized();
			norm.RotateClockwise();
			return norm;
		}
		break;
	}
}