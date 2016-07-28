#include "lesson.h"
#ifdef DRAGON_LESSON001_005

#include <d3d9.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYUP:
		switch (wParam) {
		case VK_ESCAPE:
			DestroyWindow(hWnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void initWndClass(WNDCLASS &wc, HINSTANCE hInstance) {
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"DirectX Window";
	wc.lpszMenuName = 0;
	wc.style = CS_VREDRAW | CS_HREDRAW;
}

int runMsgLoop() {
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		} else {
			//更新窗口
		}
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	//声明窗口类
	WNDCLASS wc;
	//初始化窗口类
	initWndClass(wc, hInstance);
	//注册该窗口类
	if (!RegisterClass(&wc)) {
		MessageBox(0, L"RegisterClass Failed!", L"Error", MB_OK);
	}
	//按照该窗口类创建一个窗口
	HWND hWnd = CreateWindow(L"DirectX Window", L"DirectX Window MainWindow",
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							 0, 0, hInstance, 0);
	//显示该窗口
	ShowWindow(hWnd, nCmdShow);
	//消息循环
	return runMsgLoop();
}

#endif // DRAGON_LESSON001_005