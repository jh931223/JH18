#include "stdafx.h"
#include "Camera.h"
#include "Matrix.h"
#include "Transform.h"
#include "Vector.h"

Camera::Camera():FOV(45.0f),Aspect(1.33333f),NearZ(128.0f),FarZ(100000.0f)
{
}


Camera::~Camera()
{
}

Matrix4 Camera::GenerateMatrix()
{
	Vector3 forward = transform.forward();
	Vector3 up(0, 1.0f, 0);
	Vector3 right = Vector3::Cross(forward, up);
	up = Vector3::Cross(right, forward);
	Matrix4 RMatrix;
	RMatrix.SetIdentity();
	RMatrix._11 = right.X;
	RMatrix._12 = right.Y;
	RMatrix._13 = right.Z;
	RMatrix._21 = up.X;
	RMatrix._22 = up.Y;
	RMatrix._23 = up.Z;
	RMatrix._31 = forward.X;
	RMatrix._32 = forward.Y;
	RMatrix._33 = forward.Z;
	viewMatrix = RMatrix;
	return RMatrix;
}

Matrix4 Camera::GetViewMatrix()
{

	return viewMatrix;
}
