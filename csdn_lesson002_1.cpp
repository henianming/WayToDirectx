#include "lesson.h"
#ifdef CSDN_LESSON002_1

#include <d3dx9.h>

//窗口类名宏定义
#define WND_CLASS01 L"csdn_lesson002_001_class"
//窗口名宏定义
#define WND_NAME01 L"csdn_lesson002_001_wnd"

LPDIRECT3D9 d3dManager = NULL;
LPDIRECT3DDEVICE9 d3dDevice = NULL;

//自定函数声明
LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool initailizeD3D(HWND hwnd);
VOID renderSence();
VOID shutDown();

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpCmdLine, INT nCmdShow) {
	INT posX = 25;
	INT posY = 25;
	unsigned INT width = 1024;
	unsigned INT height = 768;

	//声明窗口类
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = WND_CLASS01;

	//注册窗口类
	if (!RegisterClassEx(&wc))
		return 0;

	//创建窗口，载入注册的窗口类
	HWND hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, WND_CLASS01, WND_NAME01,
							   WS_CAPTION, posX, posY, posX + width, posY + height,
							   0, 0, hInstance, NULL);

	if (initailizeD3D(hwnd)) {
		//将窗口设置为可见
		ShowWindow(hwnd, nCmdShow);
	}

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			renderSence();
		}
	}

	shutDown();
	UnregisterClass(WND_CLASS01, hInstance);

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

bool initailizeD3D(HWND hwnd) {
	d3dManager = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3dManager == NULL)
		return false;

	D3DPRESENT_PARAMETERS d3dCfg = {};
	d3dCfg.Windowed = TRUE;
	d3dCfg.BackBufferWidth = 1024;
	d3dCfg.BackBufferHeight = 768;
	d3dCfg.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DDISPLAYMODE displayMode;
	if (FAILED(d3dManager->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		return false;
	d3dCfg.BackBufferFormat = displayMode.Format;

	if (FAILED(d3dManager->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
										hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dCfg, &d3dDevice)))
		return false;

	return true;
}

VOID renderSence() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	d3dDevice->BeginScene();
	d3dDevice->EndScene();
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

VOID shutDown() {
	if (d3dManager != NULL) {
		d3dManager->Release();
		d3dManager = NULL;
	}

	if (d3dDevice != NULL) {
		d3dDevice->Release();
		d3dDevice = NULL;
	}
}

#endif