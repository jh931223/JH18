#include "stdafx.h"
#include "Transform.h"
#include"Vector.h"
#include"Matrix.h"


Transform::Transform()
{
}


Transform::~Transform()
{
}

Matrix3 Transform::GetTRSMatrix()
{
	Matrix3 TM, RM, SM;
	TM.SetTranslation(position.X, position.Y);
	RM.SetRotation(rotation.X);
	SM.SetScale(scale.X);
	return TM*RM*SM;
}
