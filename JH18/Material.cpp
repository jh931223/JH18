#pragma once
#include "stdafx.h"
#include "Material.h"
#include"Shader.h"
#include "Mesh.h"
#include "Vertex.h"
Material::Material()
{
}


Material::~Material()
{
	if(shader)
		delete shader;
	shader = 0;
}

void Material::SetShader(Shader* _shader)
{
	if (shader)
		delete shader;
	shader = _shader;
}
void Material::DrawCall(Mesh * mesh, Matrix3 worldM,Matrix3 viewM, Matrix3 projM)
{
	if(shader)
		shader->DrawCall(mesh, viewM, worldM, projM,& params);
}
ShaderParameterCollections* Material::GetParams()
{
	return &params;
}
