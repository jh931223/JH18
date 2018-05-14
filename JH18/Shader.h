#pragma once
#include"stdafx.h"
#include"Texture.h"
#include"Vector.h"
#include"Mesh.h"
#include"Vertex.h"
#include"Triangle.h"
#include"GDIHelper.h"
#include<map>


class ShaderParameterCollections
{
	std::map<std::string, ULONG> params_Color;
	std::map<std::string, Vector3> params_Float3;
	std::map<std::string, Vector2> params_Float2;
	std::map<std::string, int> params_Int;
	std::map<std::string, float> params_Float;
	std::map<std::string, Texture*> params_Texture;
public:

	inline void SetColor(std::string name, ULONG f4) { params_Color[name] = f4; }
	inline void SetFloat3(std::string name, Vector3 f3) { params_Float3[name] = f3; }
	inline void SetFloat2(std::string name, Vector2 f2) { params_Float2[name] = f2; }
	inline void SetFloat(std::string name, float f) { params_Float[name] = f; }
	inline void SetInt(std::string name, int i) { params_Int[name] = i; }
	inline void SetTexture(std::string name, Texture* tC) { params_Texture[name] = tC; }

	inline ULONG GetColor(std::string name) { return params_Color[name]; }
	inline Vector3 GetFloat3(std::string name) { return params_Float3[name]; }
	inline Vector2 GetFloat2(std::string name) { return params_Float2[name]; }
	inline float GetFloat(std::string name) { return params_Float[name]; }
	inline int GetInt(std::string name) { return params_Int[name]; }
	inline Texture* GetTexture(std::string name) { return params_Texture[name]; }
};

struct vInput { Vector3 position; ULONG color; Vector3 normal; Vector2 texcoord; };
struct vOutput { Vector3 position; ULONG color; Vector3 normal; Vector2 texcoord; };
struct pInput { Vector3 position; ULONG color; Vector3 normal; Vector2 texcoord; };
class Shader
{
public:
	Matrix3 worldMatrix, projectionMatrix, viewMatrix;
	Shader() {}
	virtual ~Shader() {}
	virtual ULONG frag(pInput input)=0;
	virtual vOutput vert(vInput input) = 0;
	virtual void DrawCall(Mesh* mesh,Matrix3 viewMatrix, Matrix3 worldMatrix, Matrix3 projectionMatrix, ShaderParameterCollections* params) = 0;
	void Render(Mesh* mesh)
	{
		unsigned int vertid = 0;
		unsigned int* indices = mesh->GetIndices();
		Vertex* vertices = mesh->GetVertices();
		pInput pi;
		vInput vi;
		for (int i = 0; i < mesh->GetIndexSize(); i += 3)
		{
			vertid = mesh->GetIndices()[i];
			vOutput v[3];
			Vertex vertex[3];
			for (int j = 0; j < 3; j++)
			{
				vi.position = vertices[indices[i + j]].position;
				vi.color = vertices[indices[i + j]].color;
				vi.texcoord = vertices[indices[i + j]].uv;
				v[j] = vert(vi);
				vertex[j].position = v[j].position;
			}
			Triangle t(vertex[0], vertex[1], vertex[2]);
			for (int y = t.Min.Y; y <= t.Max.Y; y++)
			{
				for (int x = t.Min.X; x <= t.Max.X; x++)
				{
					Vector3 target((float)x + 0.5f, (float)y + 0.5f, 0.0f);
					float outS, outT;
					t.CalcBaryCentricCoord(target, &outS, &outT);
					if (t.IsInTrianble(outS, outT))
					{
						pi.texcoord = GetUV(outS, outT, v[0].texcoord, v[1].texcoord, v[2].texcoord);
						pi.position = GetPosition(outS, outT, v[0].position, v[1].position, v[2].position);
						pi.color = GetColor(outS, outT, v[0].color, v[1].color, v[2].color);
						g_CurrentColor = frag(pi);
						PutPixel(IntPoint(x, y));
						//gBuffer[x][y] = 1;
					}
				}
			}
		}
	}
	Vector2 GetUV(float s, float t, Vector2 uv0, Vector2 uv1, Vector2 uv2)
	{
		Vector2 UV0 = uv0;
		Vector2 UV0ToUV1 = uv1 - uv0;
		Vector2 UV0ToUV2 = uv2 - uv0;
		return UV0 + UV0ToUV1 * s + UV0ToUV2 * t;
	}
	Vector3 GetPosition(float s, float t, Vector3 p0, Vector3 p1, Vector3 p2)
	{
		Vector3 P0 = p0;
		Vector3 P0ToP1 = p1 - p0;
		Vector3 P0ToP2 = p2 - p0;
		return P0 + P0ToP1 * s + P0ToP2 * t;
	}	
	ULONG GetColor(float s, float t, ULONG c0, ULONG c1, ULONG c2)
	{
		BYTE RV0 = GetRValue(c0);
		BYTE RV1 = GetRValue(c1);
		BYTE RV2 = GetRValue(c2);

		BYTE GV0 = GetGValue(c0);
		BYTE GV1 = GetGValue(c1);
		BYTE GV2 = GetGValue(c2);

		BYTE BV0 = GetBValue(c0);
		BYTE BV1 = GetBValue(c1);
		BYTE BV2 = GetBValue(c2);

		BYTE FinalR = RoundToInt(RV0 * (1.0f - s - t) + RV1 * s + RV2 * t);
		BYTE FinalG = RoundToInt(GV0 * (1.0f - s - t) + GV1 * s + GV2 * t);
		BYTE FinalB = RoundToInt(BV0 * (1.0f - s - t) + BV1 * s + BV2 * t);
		return RGB32(FinalR, FinalG, FinalB);
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
	bool IsInRange(int x, int y)
	{
		return (abs(x) < (deviceSet.g_nClientWidth / 2)) && (abs(y) < (deviceSet.g_nClientHeight / 2));
	}
	static ULONG tex2D(Texture* _texture, Vector2 _uv)
	{
		int PixelX = (int)floorf(_uv.X*_texture->width);
		int PixelY = (int)floorf(_uv.Y*_texture->height);

		PixelX = PixelX % _texture->width;
		PixelY = PixelY % _texture->height;
		return _texture->GetPixel(PixelX, PixelY);
	}
};
