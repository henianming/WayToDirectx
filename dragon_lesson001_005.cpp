#include "lesson.h"
#ifdef DRAGON_LESSON001_005

#include <d3d9.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYUP:
		switch (wParam) {
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			return 0;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

VOID InitWNDCLASS(WNDCLASS *wc, HINSTANCE hInstance) {
	wc->cbClsExtra = 0;
	wc->cbWndExtra = 0;
	wc->hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc->hCursor = LoadCursor(0, IDC_ARROW);
	wc->hIcon = LoadIcon(0, IDI_APPLICATION);
	wc->hInstance = hInstance;
	wc->lpfnWndProc = WndProc;
	wc->lpszClassName = L"DX WND CLASS";
	wc->lpszMenuName = 0;
	wc->style = CS_HREDRAW | CS_VREDRAW;
}

bool DisplayFunc(IDirect3DDevice9 *dev, FLOAT timeInterval) {
	if (dev) {
		dev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				   0x00000000, 1.0f, 0);
		dev->Present(0, 0, 0, 0);
	}
	return true;
}

WPARAM MsgLoop(IDirect3DDevice9* dev, bool (*displayFunc)(IDirect3DDevice9*, FLOAT)) {
	MSG msg = {};

	FLOAT prevTime = (FLOAT)timeGetTime();
	FLOAT curTime;

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		} else {
			curTime = (FLOAT)timeGetTime();
			displayFunc(dev, curTime - prevTime);
			prevTime = curTime;
		}
	}
	return msg.wParam;
}

VOID InitD3DParam(D3DPRESENT_PARAMETERS *d3dPresentParam, HWND hWnd, UINT d3dWidth, UINT d3dHeight, BOOL Windowed) {
	d3dPresentParam->AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dPresentParam->BackBufferCount = 2;
	d3dPresentParam->BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dPresentParam->BackBufferHeight = d3dHeight;
	d3dPresentParam->BackBufferWidth = d3dWidth;
	d3dPresentParam->EnableAutoDepthStencil = TRUE;
	d3dPresentParam->Flags = 0;
	d3dPresentParam->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dPresentParam->hDeviceWindow = hWnd;
	d3dPresentParam->MultiSampleQuality = 0;
	d3dPresentParam->MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	d3dPresentParam->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dPresentParam->SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPresentParam->Windowed = Windowed;
}

bool Start() {
	return true;
}

VOID End() {

}



INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, INT nCmdShow) {
	WNDCLASS wc;

	InitWNDCLASS(&wc, hInstance);

	if (!RegisterClass(&wc)) {
		MessageBox(0, L"RegisterClass Failed!", L"Error", MB_OK);
		return 0;
	}

	HWND hWnd = CreateWindow(L"DX WND CLASS", L"Main Window",
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
	D3DPRESENT_PARAMETERS d3dParam;
	InitD3DParam(&d3dParam, hWnd, rect.right - rect.left, rect.bottom - rect.top, TRUE);

	IDirect3DDevice9 *iDirect3dDevice9;
	HRESULT hResult = iDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
											   hWnd, behavoirFlag, &d3dParam, &iDirect3dDevice9);
	if (FAILED(hResult)) {
		MessageBox(0, L"CreateDevice Failed!", L"Error", MB_OK);
		return 0;
	}

	//------------------------------------------------------------------------------

	ShowWindow(hWnd, nCmdShow);

	if (!Start()) {
		MessageBox(0, L"Start Failed!", L"Error", MB_OK);
		return 0;
	}

	MsgLoop(iDirect3dDevice9, DisplayFunc);

	End();

	iDirect3dDevice9->Release();

	return 0;
}

#endif //DRAGON_LESSON001_005_1