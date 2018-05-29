#include "stdafx.h"
#include "Transform.h"
#include"Vector.h"
#include"Matrix.h"


Transform::Transform()
{
}

Transform::Transform(Vector3 pos, Vector3 rot, Vector3 _scale)
{
	position = pos;
	rotation = Vector3(rot.X,rot.X, rot.X);
	scale = Vector3(_scale.X, _scale.X, _scale.X);
}


Transform::~Transform()
{
}

Matrix4 Transform::GetTRSMatrix()
{
	Matrix4 TM, RM, SM;
	TM.SetTranslation(position.X, position.Y,position.Z);
	RM.SetRotation(rotation.X,rotation.Y,rotation.Z);
	SM.SetScale(scale.X,scale.Y,scale.Z);
	return TM*RM*SM;
}

Matrix4 Transform::GetRMatrix()
{
	Matrix4 RM;
	RM.SetRotation(rotation.X, rotation.Y, rotation.Z);
	return RM;
}

Matrix4 Transform::GetTMatrix()
{
	Matrix4 TM;
	TM.SetTranslation(position.X, position.Y, position.Z);
	return TM;
}

Vector3 Transform::forward()
{

	return Vector3(0,0,1)*GetRMatrix();
}
