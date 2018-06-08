#pragma once
class IME_Manager
{
private:
	std::wstring m_inputBuffer;

public:
	void MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	IME_Manager();
	~IME_Manager();
};

