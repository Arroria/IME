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
	case WM_IME_COMPOSITION:
	{
		{
			goto skipDataName;
			if (lParam & GCS_COMPATTR) cout << "GCS_COMPATTR				" << GCS_COMPATTR << endl;//�������� ���ڿ��� Ư���� �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_COMPCLAUSE) cout << "GCS_COMPCLAUSE			" << GCS_COMPCLAUSE << endl;//	�������� ���ڿ��� �� ������ �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_COMPREADATTR) cout << "GCS_COMPREADATTR			" << GCS_COMPREADATTR << endl;//���� ���������� �б� ���ڿ� Ư���� �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_COMPREADCLAUSE) cout << "GCS_COMPREADCLAUSE		" << GCS_COMPREADCLAUSE << endl;//	�������� ���ڿ��� �б� ���ڿ��� ���� �� ������ �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_COMPREADSTR) cout << "GCS_COMPREADSTR			" << GCS_COMPREADSTR << endl;//		���� ���������� �б� ���ڿ��� �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_COMPSTR) cout << "GCS_COMPSTR				" << GCS_COMPSTR << endl;//		���� �������� ���ڿ��� �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_CURSORPOS) cout << "GCS_CURSORPOS			" << GCS_CURSORPOS << endl;//�������� ���ڿ����� Ŀ�� ��ġ�� �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_DELTASTART) cout << "GCS_DELTASTART			" << GCS_DELTASTART << endl;//	�������� ���ڿ��� ���� ���� ��ġ�� �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_RESULTCLAUSE) cout << "GCS_RESULTCLAUSE			" << GCS_RESULTCLAUSE << endl;//��� ���ڿ��� �� ������ �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_RESULTREADCLAUSE) cout << "GCS_RESULTREADCLAUSE		" << GCS_RESULTREADCLAUSE << endl;//�б� ���ڿ��� �� ������ �˻��ϰų� ������Ʈ�մϴ�.
			if (lParam & GCS_RESULTREADSTR) cout << "GCS_RESULTREADSTR		" << GCS_RESULTREADSTR << endl;//�б� ���ڿ��� �˻��ϰų� ������Ʈ�Ͻʽÿ�.
			if (lParam & GCS_RESULTSTR) cout << "GCS_RESULTSTR			" << GCS_RESULTSTR << endl;//
			cout << lParam << endl;
		}
	skipDataName:

		HIMC hIMC = ImmGetContext(hWnd);
		wchar_t input[128] = { 0 };
		if (lParam & GCS_RESULTSTR)
		{
			auto len = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);
			ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, input, len);
			wcout << input << endl;
		}
		else if (lParam & GCS_COMPSTR)
		{
			auto len = ImmGetCompositionStringW(hIMC, GCS_COMPSTR, NULL, 0);
			ImmGetCompositionStringW(hIMC, GCS_COMPSTR, input, len);
			wcout << input << endl;
		}
		ImmReleaseContext(hWnd, hIMC);

		return 0;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	return 0;
}
