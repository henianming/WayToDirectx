#include "lesson.h"
#ifdef DRAGON_LESSON_EXTRA_1

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR cmdLine, int nCmdShow) {
	WNDCLASS wc;
	wc.lpszClassName = L"hello class";
	wc.hInstance = hInstance;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = 0;

	if (RegisterClass(&wc) == 0) {
		MessageBox(0, L"RegisterClass Failed!", L"Error", MB_OK);
		return;
	}

	HWND hWnd = CreateWindow(L"hello class", L"my test window",
							 WS_OVERLAPPED,
							 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							 0, 0, hInstance, 0);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		
	}

	return 0;
}

#endif // DRAGON_LESSON_EXTRA_1