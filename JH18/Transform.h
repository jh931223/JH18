#pragma once
#include"Vector.h"
#include"Matrix.h"
class Transform
{
public:
	Transform();
	Transform(Vector3 pos,Vector3 rot,Vector3 scale);
	~Transform();
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Transform* parent;
	Matrix4 GetTRSMatrix();
	Matrix4 GetRMatrix();
	Matrix4 GetTMatrix();
	Vector3 forward();
};

