#pragma once
#include "stdafx.h"
#include <stdio.h>

struct Matrix2
{
public:
	float _11, _12;
	float _21, _22;
	Matrix2() {};
	Matrix2(float m11, float m12, float m21, float m22)
	{
		_11 = m11;
		_12 = m12;
		_21 = m21;
		_22 = m22;
	};

	void SetScale(float a, float b)
	{
		SetIdentity();
		_11 = a;
		_22 = b;
	}

	void SetRotation(float deg)
	{
		float radian = Deg2Rad(deg);

		_11 = cosf(deg);
		_12 = -sinf(deg);
		_21 = sinf(deg);
		_22 = cosf(deg);
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
	};

	Matrix2 operator *(const Matrix2 Other) const;
};

struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;
	Matrix3() {};
	Matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
	{
		_11 = m11;
		_12 = m12;
		_13 = m13;
		_21 = m21;
		_22 = m22;
		_23 = m23;
		_31 = m31;
		_32 = m32;
		_33 = m33;
	};
	void SetTranslation(float InX, float InY)
	{

	}
	Matrix3 operator *(const Matrix3 Other) const;
};