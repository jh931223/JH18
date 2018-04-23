#pragma once
#include"GDIHelper.h"
class Vertex;
class Matrix3;
class IntPoint;
class Texture;
class Mesh
{
private:
	Vertex* vertices;
	size_t vertSize;
	unsigned int* indices;
	size_t indexSize;
public:
	Mesh();
	~Mesh();
	void SetVertices(Vertex* v, size_t _size);
	void SetIndices(unsigned int* i, size_t _size);
	void Render(Matrix3 matrix, Texture* _texture);
	void PutPixel(IntPoint p);
	bool IsInRange(int x, int y);
};

