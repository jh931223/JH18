#pragma once

#include "stdafx.h"
#include "Matrix.h"

struct IntPoint
{
public:
	int X;
	int Y;

public:
	IntPoint() : X(0), Y(0) {}
	IntPoint(int InX, int InY) : X(InX), Y(InY) {}

};
struct Vector2;
struct Vector3;


struct Vector2
{
public:
	float X;
	float Y;

public:
	Vector2() : X(0), Y(0) {}
	Vector2(float InX, float InY) : X(InX), Y(InY) {}

	static float Dist(const Vector2 &V1, const Vector2 &V2);
	static float DistSquared(const Vector2 &V1, const Vector2 &V2);

	Vector2 operator *(float scale) const;
	Vector2 operator *(const Matrix2 Mat) const;
	bool Equals(const Vector2& V, float Tolerance = KINDA_SMALL_NUMBER) const;

	IntPoint ToIntPoint() 
	{
		return IntPoint((int)(X), (int)(Y));
	}

	Vector3 ToVector3();

	float Dot(const Vector2 v) const
	{
		return X * v.X + Y * v.Y;
	}


	void SetPoint(float InX, float InY)
	{
		X = InX;
		Y = InY;
	}

	Vector2 operator+(const Vector2& V) const;
	Vector2 operator-(const Vector2& V) const;

};

FORCEINLINE bool Vector2::Equals(const Vector2& V, float Tolerance) const
{
	return fabs(X - V.X) <= Tolerance && fabs(Y - V.Y) <= Tolerance;
}


struct Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

	void SetPoint(float InX, float InY,float InZ=1.0f)
	{
		X = InX;
		Y = InY;
		Z = InZ;
	}

	void SetVector(float InX, float InY, float InZ = 0.0f)
	{
		X = InX;
		Y = InY;
		Z =InZ;
	}

	float Dist()
	{
		return sqrtf(DistSquared());
	}

	float DistSquared()
	{
		return X * X + Y * Y;
	}

	Vector2 ToVector2()
	{
		Vector2 result(X, Y);
		return result;
	}

	IntPoint ToIntPoint()
	{
		return IntPoint(RoundToInt(X), RoundToInt(Y));
	}

	float Dot(const Vector3 v) const
	{
		return X * v.X + Y * v.Y + Z * v.Z;
	}
	static Vector3 Cross(const Vector3 one, const Vector3 other)
	{
		return Vector3(one.Y*other.Z - one.Z*other.Y, one.Z*other.X - one.X*other.Z, one.X*other.Y - one.Y*other.X);
	}

	Vector3 operator*(float scale) const;
	Vector3 operator+(const Vector3& V) const;
	Vector3 operator-(const Vector3& V) const;
	Vector3 operator *(const Matrix3 Mat) const;
	Vector3 operator *(const Matrix4 Mat) const;
};