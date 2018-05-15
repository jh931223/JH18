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
Shader * Material::GetShader()
{
	return shader;
}
ShaderParameterCollections* Material::GetParams()
{
	return &params;
}
