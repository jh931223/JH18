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

size_t Mesh::GetIndexSize()
{
	return indexSize;
}

size_t Mesh::GetVertexSize()
{
	return vertSize;
}

Vertex * Mesh::GetVertices()
{
	return vertices;
}

unsigned int* Mesh::GetIndices()
{
	return indices;
}

