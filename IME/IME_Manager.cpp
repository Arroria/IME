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
		wcout << L"wC : " << wP << L" ULONG : " << (ULONG)wParam << endl;

		if (wP > 0xff)
		{
			wcout << L"WM_CHAR : 2¹ÙÀÌÆ® ÀÔ·Â" << endl << L" - wchar_t : " << wP << endl << L" - ulong : " << (ULONG)wP << endl;
		}

		if (wP == VK_BACK) // backspace
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
		//else if (wP == VK_RETURN)
		//{
		//	m_inputBuffer += 0x0a;
		//	// reserved code
		//	// ¾ê°¡ °ÂÇàÇØÁÜ
		//}
		else if (wP < 32)
			; // ¤±¤©
		else
			m_inputBuffer += wP;

		return;
	}




	case WM_IME_NOTIFY: // ¹ºÁö¸ð¸§ ¾Æ¸¶ ³ªÁß¿¡ ÇÊ¿äÇÒ²¨ÀÓ
		return;
	}
}



std::wstring IME_Manager::GetString()	{ return m_inputBuffer + m_typingData; }
void IME_Manager::Clear()				{ m_inputBuffer.clear();	m_typingData.clear(); }
