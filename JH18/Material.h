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
	void DrawCall(Mesh* mesh,Matrix3,Matrix3 viewM,Matrix3 projM);
	ShaderParameterCollections* GetParams();
	int layer;
};

