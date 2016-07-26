#include "lesson.h"
#ifdef DRAGON_LESSON_EXTRA_1

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

}

int run() {
	while (::GetMessage() != 0) {

	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR cmdStr, int nCmdShow) {
	WNDCLASS wc;
	wc.lpszClassName = L"hello";
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;

	if (FAILED(RegisterClass(&wc))) {
		return 0;
	}

	HWND hWnd = CreateWindow(L"hello", L"wndname",
				 WS_OVERLAPPEDWINDOW,
				 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				 0, 0, hInstance, 0);

	ShowWindow(hWnd, nCmdShow);

	return 0;
}

#endif // DRAGON_LESSON_EXTRA