#pragma once

#include "DeviceSet.h"

extern ULONG g_CurrentColor;
extern BYTE *g_pBits;
extern DeviceSet deviceSet;
extern BYTE **gBuffer;
void InitGDI(HWND hWnd);
void ReleaseGDI(HWND hWnd);
void SetColor(BYTE r, BYTE g, BYTE b, BYTE a = 255);
void Clear();
void BufferSwap();
