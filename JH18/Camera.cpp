#include "stdafx.h"
#include "Camera.h"
#include "Matrix.h"
#include "Transform.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::RecalcMatrix()
{
	Matrix3 T, R;
	T.SetTranslation(-transform.position.X, -transform.position.Y);
	R.SetRotation(transform.rotation.X);
}

Matrix3 Camera::GetViewMatrix()
{
	return viewMatrix;
}
