#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "TextureShader.h"
#include <vector>
#include<algorithm>
#include"Transform.h"
#include"SpriteRenderer.h"
bool IsInRange(int x, int y)
{
	return (abs(x) < (deviceSet.g_nClientWidth / 2)) && (abs(y) < (deviceSet.g_nClientHeight / 2));
}

void PutPixel(IntPoint pt)
{
	if (!IsInRange(pt.X, pt.Y)) return;

	ULONG* dest = (ULONG*)g_pBits;

	int halfWidth = RoundToInt(deviceSet.g_nClientWidth * 0.5f);
	int halfHeight = RoundToInt(deviceSet.g_nClientHeight * 0.5f);

	DWORD offset = (halfHeight * deviceSet.g_nClientWidth - deviceSet.g_nClientWidth * pt.Y) + (halfWidth + pt.X);
	*(dest + offset) = g_CurrentColor;
}


void DrawLine(const Vector3& start, const Vector3& end)
{
	float length = (end - start).Dist();
	float inc = 1.0f / length;

	int maxLength = RoundToInt(length);
	for (int i = 0; i <= maxLength; i++)
	{
		float t = inc * i;
		if (t >= length) t = 1.0f;
		Vector3 Pt = start * (1.0f - t) + end * t;
		PutPixel(Pt.ToIntPoint());
	}
}





std::vector<SpriteRenderer*> rendererArray;

SpriteRenderer renderer1;
SpriteRenderer renderer2;
SpriteRenderer renderer3;
SpriteRenderer renderer4;

Material mat1;
Material mat2;

Mesh mesh1;
Mesh mesh2;

Texture* g_Texture;


bool comp(SpriteRenderer* r1, SpriteRenderer* r2)
{
	return r1 < r2;
}
void InitFrame(void)
{

	// 텍스쳐 셋
	g_Texture = new Texture;
	g_Texture->LoadBMP("test.bmp");

	// 머티리얼 셋

	mat1.SetShader(new TextureShader);
	mat1.GetParams()->SetTexture("MainTex", g_Texture);
	mat1.GetParams()->SetColor("TintColor", RGB32(255, 0, 0));
	mat1.GetParams()->SetFloat2("Offset", Vector2(0.125f, 0.125f));


	mat2.SetShader(new TextureShader);
	mat2.GetParams()->SetTexture("MainTex", g_Texture);
	mat2.GetParams()->SetColor("TintColor", RGB32(0, 35, 35));
	mat2.GetParams()->SetFloat2("Offset", Vector2(0.25f, 0.25f));

	// 메쉬 셋

	Vector3 Pt1, Pt2, Pt3, Pt4;
	Pt1.SetPoint(-150, 150.0f);
	Pt2.SetPoint(150.0f, 150.0f);
	Pt3.SetPoint(150.0f, -150.0f);
	Pt4.SetPoint(-150.0f, -150.0f);

	Vertex v1(Pt1);
	v1.color = RGB32(255, 0, 0);
	v1.uv = Vector2(0, 0);
	Vertex v2(Pt2);
	v2.color = RGB32(0, 255, 0);
	v2.uv = Vector2(0.125f, 0);
	Vertex v3(Pt3);
	v3.color = RGB32(0, 0, 255);
	v3.uv = Vector2(0.125f, 0.125f);
	Vertex v4(Pt4);
	v4.color = RGB32(255, 255, 0);
	v4.uv = Vector2(0, 0.125f);

	Vertex *v = new Vertex[4]{ v1,v2,v3,v4 };
	unsigned int *indices = new unsigned int[6]{ 0,1,2,0,2,3 };
	mesh1.SetVertices(v, 4);
	mesh1.SetIndices(indices, 6);

	////////////////////렌더러 셋
	Transform tr;

	{
		tr.position = Vector3(100, 0, 0), tr.rotation = Vector3(0, 0, 0), tr.scale = Vector3(1, 1, 1);
		renderer1.SetRenderer(tr, &mat1, &mesh1, 2);
		rendererArray.push_back(&renderer1);
	}

	{ 
		tr.position = Vector3(-100, 0, 0), tr.rotation = Vector3(0, 0, 0), tr.scale = Vector3(1, 1, 1);
		renderer2.SetRenderer(tr, &mat2, &mesh1, 1);
		rendererArray.push_back(&renderer2);
	}

	std::sort(rendererArray.begin(), rendererArray.end(), comp);
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw

	float offsetX = 0.0f;
	float angle = 0.0f;
	float scale = 0.0f;

	if (GetAsyncKeyState(VK_LEFT)) offsetX -= 1.0f;
	if (GetAsyncKeyState(VK_RIGHT)) offsetX += 1.0f;
	if (GetAsyncKeyState(VK_UP)) angle += 1.0f;
	if (GetAsyncKeyState(VK_DOWN)) angle -= 1.0f;
	if (GetAsyncKeyState(VK_PRIOR)) scale += 0.1f;
	if (GetAsyncKeyState(VK_NEXT)) scale -= 0.1f;
	renderer1.transform.position =renderer1.transform.position + Vector3(offsetX, 0,0);
	renderer1.transform.rotation = renderer1.transform.rotation + Vector3(angle, angle, angle);
	renderer1.transform.scale = renderer1.transform.scale + Vector3(scale, scale, scale);

	Matrix3 viewMatrix, projMatrix;
	for (auto i : rendererArray)
	{
		i->DrawCall(viewMatrix, projMatrix);
	}

	//Triangle T2(v1, v4, v3);

	//Draw2DTriangle(T1);
	//Draw2DTriangle(T2);

	// Buffer Swap 
	BufferSwap();
}
