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



struct SpriteRenderer
{
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Material* material;
	Mesh* mesh;
	int sortingLayer;
	SpriteRenderer() {}
	SpriteRenderer(Vector3 _p, Vector3 _rot, Vector3 _scale, Material* _m, Mesh* _me, int _sL) :position(_p), material(_m), mesh(_me), sortingLayer(_sL), rotation(_rot),scale(_scale) {}
	void SetRenderer(Vector3 _p, Vector3 _rot, Vector3 _scale, Material* _m, Mesh* _me, int _sL) { position = (_p); material = (_m); mesh = (_me); sortingLayer = (_sL); rotation = _rot; scale = _scale; }
};

std::vector<SpriteRenderer*> rendererArray;

SpriteRenderer renderer1;
SpriteRenderer renderer2;
SpriteRenderer renderer3;
SpriteRenderer renderer4;

Material mat1;

Mesh mesh1;
Mesh mesh2;

Texture* g_Texture;



void SortRenderer(std::vector<SpriteRenderer*>& _array)
{
	int maxLayer = 10;
	std::vector<SpriteRenderer*> newArray;
	for (int i = 0; i <= maxLayer; i++)
	{
		for (auto r : rendererArray)
		{
			if (r->sortingLayer > maxLayer)
				r->sortingLayer = maxLayer;
			if (r->sortingLayer == i)
			{
				newArray.push_back(r);
			}
		}
	}
	_array = newArray;
}

void InitFrame(void)
{

	// 텍스쳐 셋
	g_Texture = new Texture;
	g_Texture->LoadBMP("test.bmp");

	// 머티리얼 셋

	mat1.SetShader(new TextureShader);
	mat1.GetParams()->SetTexture("MainTex", g_Texture);
	mat1.GetParams()->SetColor("TintColor", RGB32(0, 0, 0));

	// 메쉬 셋

	Vector3 Pt1, Pt2, Pt3, Pt4;
	Pt1.SetPoint(-150, 150.0f);
	Pt2.SetPoint(150.0f, 150.0f);
	Pt3.SetPoint(150.0f, -150.0f);
	Pt4.SetPoint(-150.0f, -150.0f);

	Vertex v1(Pt1);
	v1.color = RGB32(255, 0, 0);
	v1.uv = Vector2(0.125f, 0.125f);
	Vertex v2(Pt2);
	v2.color = RGB32(0, 255, 0);
	v2.uv = Vector2(0.25f, 0.125f);
	Vertex v3(Pt3);
	v3.color = RGB32(0, 0, 255);
	v3.uv = Vector2(0.25f, 0.25f);
	Vertex v4(Pt4);
	v4.color = RGB32(255, 255, 0);
	v4.uv = Vector2(0.125f, 0.25f);

	Vertex *v = new Vertex[4];
	v[0] = v1;
	v[1] = v2;
	v[2] = v3;
	v[3] = v4;

	unsigned int *indices = new unsigned int[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;
	mesh1.SetVertices(v, 4);
	mesh1.SetIndices(indices, 6);

	Pt1.SetPoint(-150, 150.0f);
	Pt2.SetPoint(150.0f, 150.0f);
	Pt3.SetPoint(150.0f, -150.0f);
	Pt4.SetPoint(-150.0f, -150.0f);

	v1.position=(Pt1);
	v1.color = RGB32(255, 0, 0);
	v1.uv = Vector2(0.125f + 0.125f, 0.125f);
	v2.position=(Pt2);
	v2.color = RGB32(0, 255, 0);
	v2.uv = Vector2(0.25f + 0.125f, 0.125f);
	v3.position=(Pt3);
	v3.color = RGB32(0, 0, 255);
	v3.uv = Vector2(0.25f + 0.125f, 0.25f);
	v4.position=(Pt4);
	v4.color = RGB32(255, 255, 0);
	v4.uv = Vector2(0.125f + 0.125f, 0.25f);

	Vertex *vv = new Vertex[4];
	vv[0] = v1;
	vv[1] = v2;
	vv[2] = v3;
	vv[3] = v4;

	unsigned int *indices2 = new unsigned int[6];
	indices2[0] = 0;
	indices2[1] = 1;
	indices2[2] = 2;
	indices2[3] = 0;
	indices2[4] = 2;
	indices2[5] = 3;
	mesh2.SetVertices(vv, 4);
	mesh2.SetIndices(indices2, 6);

	////////////////////렌더러 셋
	renderer1.SetRenderer(Vector3(0, 100, 0),Vector3(0,0,0),Vector3(1,1,1), &mat1, &mesh1, 2);
	rendererArray.push_back(&renderer1);

	renderer2.SetRenderer(Vector3(100, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1), &mat1, &mesh2, 1);
	rendererArray.push_back(&renderer2);

	SortRenderer(rendererArray);
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
	renderer1.position =renderer1.position + Vector3(offsetX, 0,0);
	renderer1.rotation = renderer1.rotation + Vector3(angle, angle, angle);
	renderer1.scale = renderer1.scale + Vector3(scale, scale, scale);

	for (auto i : rendererArray)
	{
		Matrix3 TMat, RMat, SMat;
		TMat.SetTranslation(i->position.X,i->position.Y);
		RMat.SetRotation(i->rotation.Z);
		SMat.SetScale(i->scale.Z);
		Matrix3 TRSMat = TMat * RMat * SMat;
		i->material->DrawCall(i->mesh, TRSMat, TRSMat, TRSMat);
	}

	//Triangle T2(v1, v4, v3);

	//Draw2DTriangle(T1);
	//Draw2DTriangle(T2);

	// Buffer Swap 
	BufferSwap();
}
