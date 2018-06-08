#include "stdafx.h"
#include "MainLoop.h"
#define CREATE_CONSOLE


bool MainLoop::Initialize()
{
#ifdef CREATE_CONSOLE
	if (AllocConsole())
	{
		freopen("CONIN$", "rb", stdin);
		freopen("CONOUT$", "wb", stdout);
		freopen("CONOUT$", "wb", stderr);
	}
#endif


	cout.imbue(std::locale("kor"));
	wcout.imbue(std::locale("kor"));
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetTransform(D3DTS_PROJECTION, &MatrixPerspectiveBySprite(1280, 960));


	return true;
}

void MainLoop::Update()
{
}

bool MainLoop::Render()
{
	LPD3DXSPRITE sp;
	D3DXCreateSprite(DEVICE, &sp);
	sp->Begin(D3DXSPRITE_ALPHABLEND);
	
	LPD3DXFONT font;
	D3DXCreateFontW(DEVICE, 10, 0, 0, 0, 0, 1, 0, 0, 0, L"", &font);
	RECT rc;
	SetRect(&rc, 100, 100, 100, 100);
	font->Release();

	sp->End();
	sp->Release();
	return true;
}

bool MainLoop::Release()
{
#ifdef CREATE_CONSOLE
	FreeConsole();
#endif
	return true;
}


LRESULT MainLoop::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	return 0;
}
