#pragma once

#include "stdafx.h"

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

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;

		_21 = 0.0f;
		_22 = 1.0f;
	};

	void SetRotation(float degree)
	{
		float radian = Deg2Rad(degree);
		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = sinf(radian);
		_22 = cosf(radian);
	}

	Matrix2 operator *(const Matrix2 Other) const;
};

struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;

	Matrix3() : _11(0), _12(0), _13(0), _21(0), _22(0), _23(0), _31(0), _32(0), _33(0)
	{
	};

	void SetTranslation(float InX, float InY)
	{
		SetIdentity();
		_13 = InX;
		_23 = InY;
	}

	void SetScale(float a)
	{
		SetIdentity();
		_11 = a;
		_22 = a;
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;
		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	};

	void SetRotation(float degree)
	{
		SetIdentity();
		_11 = cosf(Deg2Rad(degree));
		_12 = -sinf(Deg2Rad(degree));
		_21 = -_12;
		_22 = _11;
	}

	void Tranpose()
	{
		float temp = _12;
		_12 = _21;
		_21 = temp;

		temp = _13;
		_13 = _31;
		_31 = temp;

		temp = _23;
		_23 = _32;
		_32 = temp;
	}

	Matrix4 operator *(const Matrix4 Other) const;
};

struct Matrix4
{
public:
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;

	Matrix4() : _11(0), _12(0), _13(0), _21(0), _22(0), _23(0), _31(0), _32(0), _33(0), _14(0), _24(0), _34(0),_41(0),_42(0),_43(0),_44(0)
	{
	};

	void SetTranslation(float InX, float InY,float InZ)
	{
		SetIdentity();
		_41 = InX;
		_42 = InY;
		_43 = InZ;
	}

	void SetScale(float x,float y,float z)
	{
		SetIdentity();
		_11 = x;
		_22 = y;
		_33 = z;
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;
		_24 = 0.0f;
		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
		_34 = 0.0f;
		_41 = 0.0f;
		_42 = 0.0f;
		_43 = 0.0f;
		_44 = 1.0f;
	};

	void SetRotation(float x,float y,float z)
	{
		SetIdentity();
		Matrix4 xMatrix;
		Matrix4 yMatrix;
		Matrix4 zMatrix;
		xMatrix.SetXRotation(x);
		yMatrix.SetYRotation(y);
		zMatrix.SetZRotation(z);
		Matrix4 result = xMatrix * yMatrix*zMatrix;
		_11 = result._11;
		_12 = result._12;
		_13 = result._13;
		_14 = result._14;

		_21 = result._21;
		_22 = result._22;
		_23 = result._23;
		_24 = result._24;

		_31 = result._31;
		_32 = result._32;
		_33 = result._33;
		_34 = result._34;

		_41 = result._41;
		_42 = result._42;
		_43 = result._43;
		_44 = result._44;
	}
	void SetXRotation(float degree)
	{
		degree = Deg2Rad(degree);
		float c = cosf(degree);
		float s = sinf(degree);
		SetIdentity();
		_22 = c;
		_23 = s;
		_32 = -s;
		_33 = c;
	}
	void SetYRotation(float degree)
	{
		degree = Deg2Rad(degree);
		float c = cosf(degree);
		float s = sinf(degree);
		SetIdentity();
		_11 = c;
		_13 = -s;
		_31 = s;
		_33 = c;
	}
	void SetZRotation(float degree)
	{
		degree = Deg2Rad(degree);
		float c = cosf(degree);
		float s = sinf(degree);
		SetIdentity();
		_11 = c;
		_12 = s;
		_21 = -s;
		_22 = c;
	}

	void Tranpose()
	{
		float temp = _12;
		_12 = _21;
		_21 = temp;

		temp = _13;
		_13 = _31;
		_31 = temp;

		temp = _14;
		_14 = _41;
		_41 = temp;

		temp = _23;
		_23 = _32;
		_32 = temp;

		temp = _24;
		_24 = _42;
		_42 = temp;

		temp = _34;
		_34 = _43;
		_43 = temp;

	}

	Matrix4 operator *(const Matrix4 Other) const;
};