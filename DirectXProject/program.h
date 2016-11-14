#ifndef PROGRAM_H
#define PROGRAM_H

#include <windows.h>

class Program {
public:
	static HRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	LARGE_INTEGER m_frequency;
	WNDCLASS m_wndClass;
	HWND m_hWnd;

private:
	void InitWndClass(HINSTANCE hInstance);
	BOOL CreateWnd(HINSTANCE hInstance, int showType);
	BOOL ReleaseWnd();
	BOOL CreateDirectX();
	BOOL ReleaseDirectX();

public:
	Program();

	BOOL Create(HINSTANCE hInstance, int showType);
	BOOL Release();
	BOOL Update();

	double GetCurTimeStamp();
};

#endif //PROGRAM_H