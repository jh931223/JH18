#pragma once
#include "Transform.h"
class Camera
{
	Transform transform;
	Matrix3 viewMatrix;
public:
	Camera();
	~Camera();
	void RecalcMatrix();
	Matrix3 GetViewMatrix();
};

