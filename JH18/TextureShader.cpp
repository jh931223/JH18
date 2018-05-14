#pragma once
#include "stdafx.h"
#include "TextureShader.h"


TextureShader::TextureShader()
{
}


TextureShader::~TextureShader()
{
}

ULONG TextureShader::frag(pInput input)
{
	ULONG color = tex2D(MainTex, input.texcoord+offSet);
	ULONG newColor;
	BYTE r = GetRValue(color)| GetRValue(TintColor);
	BYTE g = GetGValue(color)| GetGValue(TintColor);
	BYTE b = GetBValue(color)| GetBValue(TintColor);
	newColor = RGB(r,g,b,255);
	//newColor = RGB(r, g, b);
	return newColor;
}

vOutput TextureShader::vert(vInput input)
{
	vOutput output;
	output.position = input.position*worldMatrix;
	output.color = input.color;
	output.normal = input.normal;
	output.texcoord = input.texcoord;
	return output;
}

void TextureShader::DrawCall(Mesh* mesh,Matrix3 _viewMatrix, Matrix3 _worldMatrix, Matrix3 _projectionMatrix, ShaderParameterCollections * params)
{
	worldMatrix = _worldMatrix;
	viewMatrix = _viewMatrix;
	projectionMatrix = _projectionMatrix;
	MainTex = params->GetTexture("MainTex");
	TintColor = params->GetColor("TintColor");
	offSet = params->GetFloat2("Offset");
	Render(mesh);
}
