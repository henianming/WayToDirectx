#include "lesson.h"
#ifdef DRAGON_LESSON_EXTRA

#include <windows.h>

HWND MainWindowHandle = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_LBUTTONDOWN:
		::MessageBox(0, L"Hello, World", L"Hello", MB_OK);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			::DestroyWindow(MainWindowHandle);
		}
		return 0;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
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

	MainWindowHandle = ::CreateWindow(L"Hello", L"Hello",
									  WS_OVERLAPPEDWINDOW,
									  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
									  0, 0, hInstance, 0);

	if (MainWindowHandle == 0) {
		::MessageBox(0, L"CreateWindow - Failed", 0, 0);
		return false;
	}

	::ShowWindow(MainWindowHandle, show);
	::UpdateWindow(MainWindowHandle);

	return true;
}

int Run() {
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	while (::GetMessage(&msg, 0, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	return msg.wParam;
}

/*------------------------------------------------------------------------------
hInstance:当前应用程序实例的句柄
hInstancePrev:在32位的Win32编程中，不使用该参数，设置为0
lpCmdLine:运行该程序时，命令行里所输入的字符串
nCmdShow:指定应用程序窗口的显示形式
         SW_SHOWDEFAULT:以默认形式显示
		 SW_SHOWMINIMIZED:以最小化运行
		 SW_SHOWMAXIMIZED:以最大化运行
------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	if (!InitWindowsApp(hInstance, nCmdShow)) {
		::MessageBox(0, L"Init - Failed", L"Error", MB_OK);
		return 0;
	}

	return Run();
}

#endif // DRAGON_LESSON_EXTRA