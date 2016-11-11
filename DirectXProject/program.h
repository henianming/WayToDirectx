#ifndef PROGRAM_H
#define PROGRAM_H

#include <windows.h>

class Program {
public:
	static HRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE m_hInstance;
	WNDCLASS m_wndClass;
	HWND m_hWnd;

private:
	void InitWndClass();

public:
	BOOL Create(HINSTANCE hInstance);
	BOOL Release();
	BOOL DataUpdate();
	BOOL DisplayUpdate();
};

#endif //PROGRAM_H