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
			return (end - start).Normalized();
		}
		break;
		case REPEL:
		{
			return (start - end).Normalized();
		}
		break;
		case ORBIT:
		{
			Vector2 norm = (end - start).Normalized();
			norm.rotateVector(90);
			return norm;
		}
		break;
	}
}