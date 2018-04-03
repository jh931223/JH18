
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Vector.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);
void DrawCircle(Vector2, int r);
void DrawRectangle(Vector2 leftTop, Vector2 rightBottom);
Vector2 SetScale(Vector2 dotPos, int hor, int ver);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}


void DrawLine(const Vector3& p1, const Vector3& p2)
{
	Vector3 v;
	for (float i = 0; i <= 1; i += 0.0001f)
	{
		v = p1 * (1 - i) + p2 * i;
		PutPixel(v.X, v.Y);
	}
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(255, 255, 255);
	Clear();

	// Draw
	SetColor(255, 255, 0);

	DrawLine(Vector3(300, 0,1), Vector3(-100, 100,1));

	BufferSwap();
}


Vector2 SetScale(Vector2 dotPos, float scaleVal) {

	Matrix2 tempMat(scaleVal, 0, scaleVal, 0);

	return dotPos * tempMat;
}


void DrawCircle(Vector2 drawPos, int r) {

	for (int i = -r ; i < r; i++)
	{
		for (int j = -r; j < r; j++)
		{
			if ((i * i) + (j * j) < (r * r)) {
				PutPixel(i , j );

			}
		}
	}
}

void DrawRectangle(Vector2 leftTop, Vector2 rightBottom) {


	Matrix2 rot;

	static float angle = 0.0f;
	angle += 0.001f;

	rot.SetRotation(angle);
	Vector2 recTemp(5, 5);
	Vector2 NewTemp = recTemp * rot;
	PutPixel(NewTemp.X, NewTemp.Y);

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (i == j)
			{
				Vector2 recTemp(i, j);
				recTemp = recTemp * rot;
				PutPixel(recTemp.X, recTemp.Y);
			}
		}
	}

	for (int i = (int)leftTop.Y; i > (int)rightBottom.Y; i--)
	{
		for (int j = (int)leftTop.X; j < (int)rightBottom.X; j++)
		{
			Vector2 recTemp(i, j);
			recTemp = recTemp * rot;
			PutPixel(recTemp.X, recTemp.Y);
		}
	}
}
