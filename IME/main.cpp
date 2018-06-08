#include "stdafx.h"
#include "main.h"

#include "MainLoop.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	g_processManager = new ProcessManager(hInstance);
	int lastWParam = -1;

	if (SUCCEEDED( g_processManager->CreateWnd(L"UI Programing Practice", WS_POPUP, MainLoop::MsgProc) ))
	{
		g_processManager->WndResize(800, 600);
		g_processManager->WndMove(320, 60);
		g_processManager->SetFPSLimite(240, 60);
		g_processManager->SetFunction(MainLoop::Initialize, MainLoop::Update, MainLoop::Render, MainLoop::Release);
		if (SUCCEEDED( g_processManager->CreateDevice(true) ))
		{
			lastWParam = g_processManager->Loop();
			if (DEVICE)
				DEVICE->Release();
		}
	}

	return lastWParam;
}

