#include "stdafx.h"

D3DXMATRIX MatrixPerspectiveBySprite(size_t width, size_t height)
{
	/*
	2 / X			0			0	0
	0				-2 / Y		0	0
	0				0			1	0
	-(1 + 1 / X)	1 + 1 / Y	0	1
	*/
	D3DXMATRIX proj;
	ZeroMemory(&proj, sizeof(D3DXMATRIX));
	proj._33 = proj._44 = 1;
	proj._11 = 2.f / width;
	proj._22 = 2.f / height;
	proj._41 = -(1 + 1.f / width);
	proj._42 = -(1 + 1.f / height * -1);
	return proj;
}

std::random_device g_randomDevice;

ProcessManager* g_processManager = nullptr;
