#include "lesson.h"
#ifdef DRAGON_LESSON001_004

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

//------------------------------------------------------------------------------
	//IDirect3D初始化四部曲
	//1.获取指向接口IDirect3D9的指针
	IDirect3D9 *iDirect3d9; //该接口主要用途“设备枚举”及“创建IDirect3DDevice9类型的对象”
	iDirect3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	//2.校验硬件性能(以硬件顶点运算为例)
	D3DCAPS9 d3dCaps9;
	iDirect3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps9);
	DWORD BehaviorFlags = 0;
	if (d3dCaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		BehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//3.填充D3DPRESENT_PARAMETERS结构
	RECT rect;
	GetWindowRect(hWnd, &rect);
	D3DPRESENT_PARAMETERS d3dPresent_Parameters;
	d3dPresent_Parameters.BackBufferWidth = rect.right - rect.left;
	d3dPresent_Parameters.BackBufferHeight = rect.bottom - rect.top;
	d3dPresent_Parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dPresent_Parameters.BackBufferCount = 1;
	d3dPresent_Parameters.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	d3dPresent_Parameters.MultiSampleQuality = 0;
	d3dPresent_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPresent_Parameters.hDeviceWindow = hWnd;
	d3dPresent_Parameters.Windowed = TRUE;
	d3dPresent_Parameters.EnableAutoDepthStencil = TRUE;
	d3dPresent_Parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dPresent_Parameters.Flags = 0;
	d3dPresent_Parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//4.创建IDirect3DDevice9接口
	IDirect3DDevice9 *iDirect3DDevice9;
	HRESULT hResult = iDirect3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, BehaviorFlags, &d3dPresent_Parameters, &iDirect3DDevice9);
	if (FAILED(hResult)) {
		//失败
	} else {
		//成功
	}
//------------------------------------------------------------------------------

	//显示该窗口
	ShowWindow(hWnd, nCmdShow);
	//消息循环
	return runMsgLoop();
}

#endif // DRAGON_LESSON001_004