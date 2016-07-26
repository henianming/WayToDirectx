#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_LBUTTONUP:
		::MessageBox(0, L"WM_LBUTTONUP up", L"aaa", MB_OK);
		break;
	case WM_KEYUP:
		::MessageBox(0, L"WM_KEYUP up", L"aaa", MB_OK);
		break;
	case WM_CHAR:
		::MessageBox(0, L"WM_CHAR up", L"aaa", MB_OK);
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR cmdLine, int nCmdShow) {
	WNDCLASS wc;
	wc.lpszClassName = L"hello class";
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszMenuName = 0;
	wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));

	if (!RegisterClass(&wc)) {
		::MessageBox(0, L"RegisterClass failed!", L"aaa", MB_OK);
		return 0;
	}

	HWND hWnd = CreateWindow(L"hello class", L"my hello world",
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							 0, 0, hInstance, 0);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	int ret;
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while ((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
		if (ret == -1) {
			MessageBox(0, L"Message Error!", L"aaa", MB_OK);
		} else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}