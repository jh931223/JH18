#include "stdafx.h"
#include "Mesh.h"
#include "Matrix.h"
#include "GDIHelper.h"
#include "Vector.h"
#include "Triangle.h"
#include "Texture.h"
#include "Vertex.h"
Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	if (vertices)
		delete[] vertices;
	vertices = 0;
	if (indices)
		delete[] indices;
	indices = 0;
}

void Mesh::SetVertices(Vertex * v,size_t _size)
{
	if (vertices)
		delete[] vertices;
	vertices = v;
	vertSize = _size;
}

void Mesh::SetIndices(unsigned int * i, size_t _size)
{
	if (indices)
		delete[] indices;
	indices = i;
	indexSize = _size;
}

void Mesh::Render(Matrix3 matrix,Texture* _texture)
{
	unsigned int vertid = 0;
	for (int i = 0; i < indexSize; i += 3)
	{
		vertid = indices[i];
		Vertex v[3];
		for (int j = 0; j < 3; j++)
		{
			v[j].position = vertices[indices[i+j]].position*matrix;
			v[j].color = vertices[indices[i + j]].color;
			v[j].uv = vertices[indices[i + j]].uv;
		}
		Triangle t(v[0],v[1],v[2]);
		for (int y = t.Min.Y; y <= t.Max.Y; y++)
		{
			for (int x = t.Min.X; x <= t.Max.X; x++)
			{
				Vector3 target((float)x + 0.5f, (float)y + 0.5f, 0.0f);
				float outS, outT;
				t.CalcBaryCentricCoord(target, &outS, &outT);
				if (t.IsInTrianble(outS, outT))
				{
					if (_texture->IsLoaded())
					{
						g_CurrentColor = _texture->GetTexturePixel(outS, outT, t);
					}
					else
					{
						g_CurrentColor = t.GetPixelColor(target, outS, outT);
					}
					PutPixel(IntPoint(x, y));
				}
			}
		}
	}
}

void Mesh::PutPixel(IntPoint pt)
{
	if (!IsInRange(pt.X, pt.Y)) return;

	ULONG* dest = (ULONG*)g_pBits;

	int halfWidth = RoundToInt(deviceSet.g_nClientWidth * 0.5f);
	int halfHeight = RoundToInt(deviceSet.g_nClientHeight * 0.5f);

	DWORD offset = (halfHeight * deviceSet.g_nClientWidth - deviceSet.g_nClientWidth * pt.Y) + (halfWidth + pt.X);
	*(dest + offset) = g_CurrentColor;
}

bool Mesh::IsInRange(int x, int y)
{
	return (abs(x) < (deviceSet.g_nClientWidth / 2)) && (abs(y) < (deviceSet.g_nClientHeight / 2));
}