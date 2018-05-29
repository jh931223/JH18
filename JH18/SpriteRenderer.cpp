#include "stdafx.h"
#include "SpriteRenderer.h"
#include "Mesh.h"
#include "Material.h"


SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::SpriteRenderer(Transform _transform, Material * _m, Mesh * _me, int _sL)
{
	transform = (_transform); material = (_m); mesh = (_me); sortingLayer = (_sL);
}

void SpriteRenderer::SetRenderer(Transform _transform, Material * _m, Mesh * _me, int _sL)
{
	transform = (_transform); material = (_m); mesh = (_me); sortingLayer = (_sL);
}

void SpriteRenderer::DrawCall(Matrix3 viewM, Matrix3 projM)
{
	if (material->GetShader())
		material->GetShader()->DrawCall(mesh, viewM, transform.GetTRSMatrix(), projM, material->GetParams());
}


SpriteRenderer::~SpriteRenderer()
{
}
