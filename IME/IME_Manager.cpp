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