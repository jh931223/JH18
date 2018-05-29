#pragma once
#include"Material.h"
#include"Mesh.h"
#include"Transform.h"
class SpriteRenderer
{
public:
	Transform transform;
	Material* material;
	Mesh* mesh;
	int sortingLayer;
public:
	SpriteRenderer();
	SpriteRenderer(Transform _transform, Material* _m, Mesh* _me, int _sL);
	~SpriteRenderer();
	void SetRenderer(Transform _transform, Material* _m, Mesh* _me, int _sL);
	void DrawCall(Matrix3 viewM, Matrix3 projM);
};
