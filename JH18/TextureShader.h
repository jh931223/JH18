#pragma once
#include "stdafx.h"
#include "Shader.h"
#include "Texture.h"
class TextureShader :
	public Shader
{
public:
	Texture* MainTex;
	ULONG TintColor;
	Vector2 offSet;
	TextureShader();
	virtual ~TextureShader();

	// Shader을(를) 통해 상속됨
	virtual ULONG frag(pInput) override;
	virtual vOutput vert(vInput) override;
	virtual void DrawCall(Mesh* mesh,Matrix3 viewMatrix, Matrix3 worldMatrix, Matrix3 projectionMatrix, ShaderParameterCollections * params) override;
};

