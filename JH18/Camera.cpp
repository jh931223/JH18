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

Matrix3 Camera::GenerateMatrix()
{
	Matrix3 TMat, RMat;
	TMat.SetTranslation(-transform.position.X, -transform.position.Y);
	RMat.SetRotation(transform.rotation.X);
	RMat.Tranpose();
	viewMatrix= RMat * TMat;
	return viewMatrix;
}

Matrix3 Camera::GetViewMatrix()
{

	return viewMatrix;
}
