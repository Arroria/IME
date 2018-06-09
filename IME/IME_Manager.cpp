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
		{
			goto skipDataName;
			if (lParam & GCS_COMPATTR) cout << "GCS_COMPATTR				" << GCS_COMPATTR << endl;//컴포지션 문자열의 특성을 검색하거나 업데이트합니다.
			if (lParam & GCS_COMPCLAUSE) cout << "GCS_COMPCLAUSE			" << GCS_COMPCLAUSE << endl;//	컴포지션 문자열의 절 정보를 검색하거나 업데이트합니다.
			if (lParam & GCS_COMPREADATTR) cout << "GCS_COMPREADATTR			" << GCS_COMPREADATTR << endl;//현재 컴포지션의 읽기 문자열 특성을 검색하거나 업데이트합니다.
			if (lParam & GCS_COMPREADCLAUSE) cout << "GCS_COMPREADCLAUSE		" << GCS_COMPREADCLAUSE << endl;//	컴포지션 문자열의 읽기 문자열에 대한 절 정보를 검색하거나 업데이트합니다.
			if (lParam & GCS_COMPREADSTR) cout << "GCS_COMPREADSTR			" << GCS_COMPREADSTR << endl;//		현재 컴포지션의 읽기 문자열을 검색하거나 업데이트합니다.
			if (lParam & GCS_COMPSTR) cout << "GCS_COMPSTR				" << GCS_COMPSTR << endl;//		현재 컴포지션 문자열을 검색하거나 업데이트합니다.
			if (lParam & GCS_CURSORPOS) cout << "GCS_CURSORPOS			" << GCS_CURSORPOS << endl;//컴포지션 문자열에서 커서 위치를 검색하거나 업데이트합니다.
			if (lParam & GCS_DELTASTART) cout << "GCS_DELTASTART			" << GCS_DELTASTART << endl;//	컴포지션 문자열의 변경 시작 위치를 검색하거나 업데이트합니다.
			if (lParam & GCS_RESULTCLAUSE) cout << "GCS_RESULTCLAUSE			" << GCS_RESULTCLAUSE << endl;//결과 문자열의 절 정보를 검색하거나 업데이트합니다.
			if (lParam & GCS_RESULTREADCLAUSE) cout << "GCS_RESULTREADCLAUSE		" << GCS_RESULTREADCLAUSE << endl;//읽기 문자열의 절 정보를 검색하거나 업데이트합니다.
			if (lParam & GCS_RESULTREADSTR) cout << "GCS_RESULTREADSTR		" << GCS_RESULTREADSTR << endl;//읽기 문자열을 검색하거나 업데이트하십시오.
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
			m_inputBuffer += input;
			m_typingData.clear();
		}
		else if (lParam & GCS_COMPSTR)
		{
			auto len = ImmGetCompositionStringW(hIMC, GCS_COMPSTR, NULL, 0);
			ImmGetCompositionStringW(hIMC, GCS_COMPSTR, input, len);
			m_typingData = input;
		}
		ImmReleaseContext(hWnd, hIMC);

		

		wcout << m_inputBuffer + m_typingData << endl;
		break;
	}
	case WM_CHAR:

		wchar_t wP = wParam;

		if (wP == VK_BACK)
		{
			size_t size = m_inputBuffer.size();
			if (size)
				m_inputBuffer.resize(size - 1);
		}
		else if (wP == 0x7F)
		{
			size_t removeSize = 0;
			for (auto iter = m_inputBuffer.rbegin(); iter != m_inputBuffer.rend(); iter++)
			{
				removeSize++;
				if (*iter <= 32)
					break;
			}
			m_inputBuffer.resize(m_inputBuffer.size() - removeSize);
		}
		else
			m_inputBuffer += wP;

		wcout << m_inputBuffer + m_typingData << endl;
		break;
	}
}