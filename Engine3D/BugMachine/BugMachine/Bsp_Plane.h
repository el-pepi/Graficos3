#pragma once

#define DLLexport __declspec(dllexport)

#include "RenderTypes.h"
#include "Mat.h"

typedef D3DXPLANE* Plane;

enum Side
{
	Left,
	Right
};

class Bsp_Plane{
public:
	DLLexport Bsp_Plane(Plane plane);
	DLLexport void SetCameraPos(float x, float y, float z);
	DLLexport bool IsOnCorrectSide(float x, float y, float z);
	DLLexport bool IsOnCorrectSide(AABB aabb);
private:
	Side _side;
	Plane _plane;
};