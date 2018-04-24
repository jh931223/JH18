#pragma once
class Mesh;

void InitFrame(void);
void UpdateFrame(void);
bool IsInRange(int x, int y);
void PutPixel(IntPoint pt);
void DrawCall(Mesh* meshToDraw);