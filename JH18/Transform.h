#pragma once
#include"Vector.h"
#include"Matrix.h"
class Transform
{
public:
	Transform();
	~Transform();
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Transform* parent;
	Matrix3 GetTRSMatrix();
};

