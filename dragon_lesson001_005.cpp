#include "lesson.h"
#ifdef DRAGON_LESSON001_005

#include "d3d9.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYUP:
		switch (wParam) {
		case VK_RETURN:
			MessageBox(0, L"Enter", L"Msg", MB_OK);
			break;
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void InitWNDCLASS(WNDCLASS &wc, HINSTANCE hInstance) {
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Direct Main Window Class";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
}

void MsgLoop() {
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		}
	}
}

void InitD3DPRESENT_PARAMETERS(D3DPRESENT_PARAMETERS &d3dPresent_Parameters, HWND hWnd, LONG width, LONG height, BOOL Windowed) {
	d3dPresent_Parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dPresent_Parameters.BackBufferCount = 2;
	d3dPresent_Parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dPresent_Parameters.BackBufferHeight = height;
	d3dPresent_Parameters.BackBufferWidth = width;
	d3dPresent_Parameters.EnableAutoDepthStencil = TRUE;
	d3dPresent_Parameters.Flags = 0;
	d3dPresent_Parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dPresent_Parameters.hDeviceWindow = hWnd;
	d3dPresent_Parameters.MultiSampleQuality = 0;
	d3dPresent_Parameters.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	d3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dPresent_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPresent_Parameters.Windowed = Windowed;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR cmdLine, int showWindowCommand) {
	WNDCLASS wc;

	InitWNDCLASS(wc, hInstance);

	if (!RegisterClass(&wc)) {
		MessageBox(0, L"RegisterClass Failed!", L"Error", MB_OK);
	}

	HWND hWnd = CreateWindow(L"Direct Main Window Class", L"Direct Main Window",
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							 0, 0, hInstance, 0);

//------------------------------------------------------------------------------
	IDirect3D9 *iDirect3D9;
	iDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 d3dCaps9;
	iDirect3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps9);
	DWORD behavoirFlag;
	if (d3dCaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		behavoirFlag = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		behavoirFlag = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	RECT rect;
	GetWindowRect(hWnd, &rect);
	D3DPRESENT_PARAMETERS d3dPresent_Parameters;
	InitD3DPRESENT_PARAMETERS(d3dPresent_Parameters, hWnd, rect.right - rect.left, rect.bottom - rect.top, TRUE);

	IDirect3DDevice9 *iDirect3DDevice9;
	HRESULT hResult = iDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, behavoirFlag, &d3dPresent_Parameters, &iDirect3DDevice9);
//------------------------------------------------------------------------------

	ShowWindow(hWnd, showWindowCommand);

	MsgLoop();
	return 0;
}

#endif // DRAGON_LESSON001_005