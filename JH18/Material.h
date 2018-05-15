#pragma once
#include"Vector.h"
#include"Matrix.h"
#include"Shader.h"
class Mesh;
class ShaderParameterCollections;
class Shader;
class Material
{
	Shader* shader;
	ShaderParameterCollections params;
public:
	Material();
	~Material();
	void SetShader(Shader*);
	Shader* GetShader();
	ShaderParameterCollections* GetParams();
	int layer;
};

