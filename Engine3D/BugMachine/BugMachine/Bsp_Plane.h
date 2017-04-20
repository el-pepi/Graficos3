#ifndef BSP_PLANE_H
#define BSP_PLANE_H
#define DLLexport __declspec(dllexport)

#include "Mesh.h"

enum Side
{
	Left,
	Right,
	Both
};

class Bsp_Plane{
public:
	DLLexport Bsp_Plane();
	DLLexport void SetCameraPos(float x, float y, float z);
private:
	Plane plane;
	Mesh mesh;
	Side side;
};


#endif