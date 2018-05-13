#pragma once
class Vertex;
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
	size_t GetIndexSize();
	size_t GetVertexSize();
	Vertex* GetVertices();
	unsigned int* GetIndices();
};

