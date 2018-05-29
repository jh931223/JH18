#pragma once
#include "Transform.h"
class Camera
{
	Matrix4 viewMatrix;
public:
	Camera();
	~Camera();
	Transform transform;
	float FOV,Aspect,NearZ,FarZ;
	Matrix4 GenerateMatrix();
	Matrix4 GetViewMatrix();
};

