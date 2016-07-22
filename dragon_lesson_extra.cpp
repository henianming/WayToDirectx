#include "lesson.h"
#ifdef DRAGON_LESSON_EXTRA

#include <windows.h>

HWND MainWindowHandle = 0;

bool InitWindowsApp(HINSTANCE hInstance, int show);

int Run();

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	if (!InitWindowsApp(hInstance, nCmdShow)) {
		::MessageBox(0, L"Init - Failed", L"Error", MB_OK);
		return 0;
	}

	return Run();
}

bool InitWindowsApp(HINSTANCE hInstance, int show) {
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = ::LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"Hello";

	if (!::RegisterClass(&wc)) {
		::MessageBox(0, L"RegisterClass - Failed", 0, 0);
		return false;
	}

	MainWindowHandle = ::CreateWindow()
}

#endif // DRAGON_LESSON_EXTRA