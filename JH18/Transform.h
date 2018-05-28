#pragma once
#include"Vector.h"
#include"Matrix.h"
class Transform2D
{
public:
	Transform2D();
	Transform2D(Vector3 pos,Vector3 rot,Vector3 scale);
	~Transform2D();
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Transform2D* parent;
	Matrix3 GetTRSMatrix();
	Matrix3 GetRMatrix();
	Matrix3 GetTMatrix();
};

