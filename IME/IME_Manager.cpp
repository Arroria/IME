#include "stdafx.h"
#include "IME_Manager.h"


IME_Manager::IME_Manager()
{
	m_inputBuffer.clear();
}
IME_Manager::~IME_Manager()
{
}


void IME_Manager::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_IME_COMPOSITION:
	{
		HIMC hIMC = ImmGetContext(hWnd);
		wchar_t input[128] = { 0 };
		if (lParam & GCS_RESULTSTR)
		{
			auto len = ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, NULL, 0);
			ImmGetCompositionStringW(hIMC, GCS_RESULTSTR, input, len);
			m_typingData.clear();
		}
		else if (lParam & GCS_COMPSTR)
		{
			auto len = ImmGetCompositionStringW(hIMC, GCS_COMPSTR, NULL, 0);
			ImmGetCompositionStringW(hIMC, GCS_COMPSTR, input, len);
			m_typingData = input;
		}
		ImmReleaseContext(hWnd, hIMC);
		return;
	}

	case WM_CHAR:
	{
		wchar_t wP = wParam;

		if (wP > 0xff)
		{
			wcout << L"WM_CHAR : 2바이트 입력" << endl << L" - wchar_t : " << wP << endl << L" - ulong : " << (ULONG)wP << endl;
		}
		if (wP == VK_BACK)
		{
			size_t size = m_inputBuffer.size();
			if (size)
				m_inputBuffer.resize(size - 1);
		}
		else if (wP == 0x7F) // ctrl + backspace
		{
			size_t removeSize = 0;
			bool firstWhitespaceIgnore = false;
			for (auto iter = m_inputBuffer.rbegin(); iter != m_inputBuffer.rend(); iter++)
			{
				if (*iter <= 32 && firstWhitespaceIgnore)
					break;

				removeSize++;
				firstWhitespaceIgnore = true;
			}
			m_inputBuffer.resize(m_inputBuffer.size() - removeSize);
		}
		else
			m_inputBuffer += wP;

		return;
	}




	case WM_IME_NOTIFY: // 뭔지모름 아마 나중에 필요할꺼임
		return;
	}
}



std::wstring IME_Manager::GetString()
{
	//wcout << m_inputBuffer + m_typingData << endl;
	return m_inputBuffer + m_typingData;
}
