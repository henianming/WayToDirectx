#include "lesson.h"
#ifdef CSDN_LESSON001

#include <d3dx9.h>

#define WND_CLASS01 L"csdn_lesson001_001_class"

#define WND_NAME01 L"csdn_lesson001_001_wnd"

LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow) {
	int posX = 25;
	int posY = 25;
	unsigned int width = 1024;
	unsigned int height = 768;

	//����������
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = WND_CLASS01;

	//ע�ᴰ����
	if (!RegisterClassEx(&wc))
		return 0;

	//�������ڣ�����ע��Ĵ�����
	HWND hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, WND_CLASS01, WND_NAME01,
							   WS_CAPTION, posX, posY, posX + width, posY + height,
							   0, 0, hInstance, NULL);

						   //����������Ϊ�ɼ�
	ShowWindow(hwnd, nCmdShow);

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_KEYUP:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		default:
			return 0;
		}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

#endif