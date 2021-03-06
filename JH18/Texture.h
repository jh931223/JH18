#pragma once
#include "stdafx.h"

class Texture
{
public:
	Texture() : Buffer(NULL), width(0), height(0) {}
	~Texture() { if (Buffer != NULL) delete Buffer; }

	bool IsLoaded() { return (Buffer != NULL);  }

	bool LoadBMP(char* filename);
	ULONG GetPixel(int x, int y);

	int width;
	int height;
	ULONG* Buffer;
};