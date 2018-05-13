
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
// 변수
ULONG g_CurrentColor;
BYTE *g_pBits;
BYTE** gBuffer;
HDC	hScreenDC, hMemoryDC;
HBITMAP hDefaultBitmap, hDIBitmap;
DeviceSet deviceSet;


// 함수

void BufferSwap()
{
	BitBlt(hScreenDC, 0, 0, deviceSet.g_nClientWidth, deviceSet.g_nClientHeight, hMemoryDC, 0, 0, SRCCOPY);
}

void SetColor(BYTE r, BYTE g, BYTE b, BYTE a)
{
	g_CurrentColor = RGBA32(r, g, b, a);
}

void Clear()
{
	ULONG* dest = (ULONG*)g_pBits;
	DWORD bytecount = deviceSet.g_nClientWidth * deviceSet.g_nClientHeight * sizeof(ULONG);
	ULONG value = g_CurrentColor;
	bytecount /= 4;
	while (bytecount--)
	{
		*dest++ = value;
	}
	//for (int i = 0; i < deviceSet.g_nClientWidth; i++)
	//{
	//	for (int j = 0; j < deviceSet.g_nClientHeight; j++)
	//		gBuffer[i][j] = 255;
	//}
	return;
}

void InitGDI(HWND hWnd)
{
	hScreenDC = GetDC(hWnd);
	hMemoryDC = CreateCompatibleDC(hScreenDC);

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = deviceSet.g_nClientWidth;
	bmi.bmiHeader.biHeight = -deviceSet.g_nClientHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	hDIBitmap = CreateDIBSection(hMemoryDC, &bmi, DIB_RGB_COLORS, (void**)&g_pBits, NULL, 0);
	hDefaultBitmap = (HBITMAP)SelectObject(hMemoryDC, hDIBitmap);

	g_bIsActive = TRUE;

	gBuffer = new BYTE*[deviceSet.g_nClientWidth];
	for (int i = 0; i < deviceSet.g_nClientWidth; i++)
	{
		gBuffer[i] = new BYTE[deviceSet.g_nClientHeight];
		for (int j = 0; j < deviceSet.g_nClientHeight; j++)
			gBuffer[i][j] = 255;
	}
}

void ReleaseGDI(HWND hWnd)
{
	g_bIsActive = FALSE;

	DeleteObject(hDefaultBitmap);
	DeleteObject(hDIBitmap);
	ReleaseDC(hWnd, hScreenDC);
	ReleaseDC(hWnd, hMemoryDC);

	if (gBuffer)
	{
		for (int i = 0; i < deviceSet.g_nClientWidth; i++)
		{
			delete[] gBuffer[i];
		}
		delete[] gBuffer;
	}
}


