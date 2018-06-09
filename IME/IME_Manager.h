#pragma once
class IME_Manager
{
private:
	std::wstring m_inputBuffer;

	std::wstring m_typingData;

public:
	void MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	IME_Manager();
	~IME_Manager();
};

