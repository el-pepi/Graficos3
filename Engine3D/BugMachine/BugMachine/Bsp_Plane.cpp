#include "Bsp_Plane.h"

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

Bsp_Plane::Bsp_Plane(Plane plane){
	_plane = plane;
}

void Bsp_Plane::SetCameraPos(float x, float y, float z){
	if (D3DXPlaneDotCoord(_plane, &D3DXVECTOR3(x, y, z)) > 0) {
		_side = Left;
	}
	else {
		_side = Right;
	}
}

bool Bsp_Plane::IsOnCorrectSide(float x, float y, float z)
{
	return false;
}
bool Bsp_Plane::IsOnCorrectSide(AABB aabb)
{
	D3DXVECTOR3 aabbVertices[8] =
	{
		D3DXVECTOR3(aabb.ActualxMin, aabb.ActualyMin, aabb.ActualzMin),
		D3DXVECTOR3(aabb.ActualxMax, aabb.ActualyMax, aabb.ActualzMax),
		D3DXVECTOR3(aabb.ActualxMax, aabb.ActualyMin, aabb.ActualzMax),
		D3DXVECTOR3(aabb.ActualxMax, aabb.ActualyMax, aabb.ActualzMin),
		D3DXVECTOR3(aabb.ActualxMax, aabb.ActualyMin, aabb.ActualzMin),
		D3DXVECTOR3(aabb.ActualxMin, aabb.ActualyMin, aabb.ActualzMax),
		D3DXVECTOR3(aabb.ActualxMin, aabb.ActualyMax, aabb.ActualzMax),
		D3DXVECTOR3(aabb.ActualxMin, aabb.ActualyMax, aabb.ActualzMin)
	};

	for (int i = 0; i < 8; i++) {
		if (D3DXPlaneDotCoord(_plane, &aabbVertices[i]) > 0) {
			if (_side == Left) {
				return true;
			}
		}
		else
		{
			if (_side == Right) {
				return true;
			}
		}
	}

	return true;
}
