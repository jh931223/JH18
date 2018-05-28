#pragma once
#include "Transform.h"
class Camera
{
	Matrix3 viewMatrix;
public:
	Camera();
	~Camera();
	Transform2D transform;
	Matrix3 GenerateMatrix();
	Matrix3 GetViewMatrix();
};

