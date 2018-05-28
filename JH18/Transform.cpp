#include "stdafx.h"
#include "Transform.h"
#include"Vector.h"
#include"Matrix.h"


Transform2D::Transform2D()
{
}

Transform2D::Transform2D(Vector3 pos, Vector3 rot, Vector3 _scale)
{
	position = pos;
	rotation = Vector3(rot.X,rot.X, rot.X);
	scale = Vector3(_scale.X, _scale.X, _scale.X);
}


Transform2D::~Transform2D()
{
}

Matrix3 Transform2D::GetTRSMatrix()
{
	Matrix3 TM, RM, SM;
	TM.SetTranslation(position.X, position.Y);
	RM.SetRotation(rotation.X);
	SM.SetScale(scale.X);
	return TM*RM*SM;
}

Matrix3 Transform2D::GetRMatrix()
{
	Matrix3 RM;
	RM.SetRotation(rotation.X);
	return RM;
}

Matrix3 Transform2D::GetTMatrix()
{
	Matrix3 TM;
	TM.SetTranslation(position.X, position.Y);
	return TM;
}