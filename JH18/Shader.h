#pragma once
#include"stdafx.h"
#include"Vector.h"
#include"Texture.h"

ULONG tex2D(Texture* _texture, Vector2 _uv)
{
	return _texture->GetPixel((int)(_uv.X*_texture->width), (int)(_uv.Y*_texture->height));
}

class Shader
{
protected:
	Texture* tSampler;
public:
	struct vInput { Vector3 position; ULONG color; Vector3 normal; Vector2 texcoord; };
	struct vOutput { Vector3 position; ULONG color; Vector3 normal; Vector2 texcoord; };
	Shader();
	virtual ~Shader();
	virtual ULONG frag(vOutput)=0;
	virtual vOutput vert(vInput) = 0;
	void Render(Matrix3 viewMatrix, Matrix3 worldMatrix, Matrix3 projectionMatrix, Texture* t, Vertex* vertBuffer, unsigned int* indexBuffer)
	{

	}
private:
	
};

Shader::Shader()
{
}

Shader::~Shader()
{
}