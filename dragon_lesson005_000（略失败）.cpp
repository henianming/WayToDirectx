#include "lesson.h"
#ifdef DRAGON_LESSON005_000

#include <d3d9.h>
#include <d3dx9math.h>
#include <sstream>
#include <iostream>

IDirect3DDevice9 *device = 0;
ID3DXMesh *mesh = 0;

IDirect3DVertexBuffer9 *vb = 0;
IDirect3DIndexBuffer9 *ib = 0;
INT wndWidth = 0;
INT wndHeight = 0;
FLOAT g_speed = 0.1F;
FLOAT g_X = 0.0F;
FLOAT g_Y = 0.0F;
bool g_mouseDown = false;
POINT g_lPoint = {0};
FLOAT g_lX = 0.0F;
FLOAT g_lY = 0.0F;

class MyVertex {
public:
	MyVertex() {

	}

	MyVertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz)
		: m_x(x), m_y(y), m_z(z), m_nx(nx), m_ny(ny), m_nz(nz) {
	}

	FLOAT m_x, m_y, m_z;
	FLOAT m_nx, m_ny, m_nz;
	static DWORD const FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
};

bool Setup(IDirect3DDevice9 *device) {
	device->CreateVertexBuffer(
		8 * sizeof(MyVertex),
		D3DUSAGE_WRITEONLY,
		MyVertex::FVF,
		D3DPOOL_MANAGED,
		&vb,
		0
	);

	device->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib,
		0
	);

	MyVertex *vertex;
	vb->Lock(0, 0, (VOID**)&vertex, 0);

	vertex[0] = MyVertex(-1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F);
	vertex[1] = MyVertex(-1.0F,  1.0F, -1.0F, -1.0F,  1.0F, -1.0F);
	vertex[2] = MyVertex( 1.0F,  1.0F, -1.0F,  1.0F,  1.0F, -1.0F);
	vertex[3] = MyVertex( 1.0F, -1.0F, -1.0F,  1.0F, -1.0F, -1.0F);
	vertex[4] = MyVertex(-1.0F, -1.0F,  1.0F, -1.0F, -1.0F,  1.0F);
	vertex[5] = MyVertex(-1.0F,  1.0F,  1.0F, -1.0F,  1.0F,  1.0F);
	vertex[6] = MyVertex( 1.0F,  1.0F,  1.0F,  1.0F,  1.0F,  1.0F);
	vertex[7] = MyVertex( 1.0F, -1.0F,  1.0F,  1.0F, -1.0F,  1.0F);

	vb->Unlock();

	WORD *idx = 0;
	ib->Lock(0, 0, (VOID**)&idx, 0);

	WORD idxs[36] = {
		0,1,2,
		0,2,3,
		4,6,5,
		4,7,6,
		4,5,1,
		4,1,0,
		3,2,6,
		3,6,7,
		1,5,6,
		1,6,2,
		4,0,3,
		4,3,7
	};
	for (INT i = 1; i < 36; i++) {
		idx[i] = idxs[i];
	}

	ib->Unlock();

	D3DMATERIAL9 mtrl;
	mtrl.Ambient = D3DXCOLOR(D3DCOLOR_ARGB(255, 0, 255, 0));
	mtrl.Diffuse = D3DXCOLOR(D3DCOLOR_ARGB(255, 0, 255, 0));
	mtrl.Specular = D3DXCOLOR(D3DCOLOR_ARGB(255, 0, 255, 0));
	mtrl.Emissive = D3DXCOLOR(D3DCOLOR_ARGB(255, 0, 255, 0));
	mtrl.Power = 5.0F;

	device->SetMaterial(&mtrl);

	D3DXCreateSphere(device, 1.5F, 100, 100, &mesh, NULL);

	D3DLIGHT9 light;
	memset(&light, 0, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(D3DCOLOR_ARGB(255, 255, 255, 255));
	light.Specular = D3DXCOLOR(D3DCOLOR_ARGB(255, 255, 255, 255)) * 0.3F;
	light.Ambient = D3DXCOLOR(D3DCOLOR_ARGB(255, 255, 255, 255)) * 0.6F;
	light.Direction = D3DXVECTOR3(1.0F, 0.0F, 1.0F);

	device->SetLight(0, &light);
	device->LightEnable(0, TRUE);

	device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	device->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DXVECTOR3 position(0.0F, 0.0F, -5.0F);
	D3DXVECTOR3 target(0.0F, 0.0F, 0.0F);
	D3DXVECTOR3 up(0.0F, 1.0F, 0.0F);

	D3DXMATRIX v;

	D3DXMatrixLookAtLH(&v, &position, &target, &up);
	device->SetTransform(D3DTS_VIEW, &v);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5F,
		(FLOAT)wndWidth / (FLOAT)wndHeight,
		1.0F,
		1000.0F
	);
	device->SetTransform(D3DTS_PROJECTION, &proj);

	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	device->SetRenderState(D3DRS_LIGHTING, false);

	return true;
}

VOID SetDefRenderState(IDirect3DDevice9 *dev) {

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYUP:
		switch (wParam) {
		case VK_UP:
			g_X += g_speed;
			break;
		case VK_DOWN:
			g_X -= g_speed;
			break;
		case VK_LEFT:
			g_Y -= g_speed;
			break;
		case VK_RIGHT:
			g_Y += g_speed;
			break;
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			return 0;
		case 'Z':
		{
			DWORD out;
			device->GetRenderState(D3DRS_FILLMODE, &out);
			out++;
			if (out == 4) {
				out = 1;
			}
			device->SetRenderState(D3DRS_FILLMODE, out);
		}
			return 0;
		case 'X':
		{
			DWORD out;
			device->GetRenderState(D3DRS_MULTISAMPLEANTIALIAS, &out);
			out = !(bool)out;
			device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, out);
		}
			return 0;
		case 'C':
		{
			DWORD out;
			device->GetRenderState(D3DRS_CULLMODE, &out);
			out++;
			if (out == 4) {
				out = 1;
			}
			device->SetRenderState(D3DRS_CULLMODE, out);
		}
			return 0;
		case 'V':
		{
			DWORD out;
			device->GetRenderState(D3DRS_SHADEMODE, &out);
			out++;
			if (out == 4) {
				out = 1;
			}
			device->SetRenderState(D3DRS_SHADEMODE, out);
		}
		return 0;
		case 'B':
		{
			DWORD out;
			device->GetRenderState(D3DRS_LIGHTING, &out);
			out = !(bool)out;
			device->SetRenderState(D3DRS_LIGHTING, out);
		}
		return 0;
		}
		return 0;
	case WM_LBUTTONDOWN:
		g_mouseDown = true;
		GetCursorPos(&g_lPoint);
		g_lX = g_X;
		g_lY = g_Y;
		return 0;
	case WM_MOUSEMOVE:
		if (g_mouseDown) {
			POINT tempPoint;
			GetCursorPos(&tempPoint);
			g_Y = g_lY - (tempPoint.x - g_lPoint.x) / 360.0F;
			g_X = g_lX - (tempPoint.y - g_lPoint.y) / 360.0F;
		}
		return 0;
	case WM_LBUTTONUP:
		g_mouseDown = false;
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

bool DisplayFunc(HWND hwnd, IDirect3DDevice9 *dev, FLOAT timeInterval) {
	INT fps = (INT)(30.0F / timeInterval);
	wchar_t wc[256];
	swprintf(wc, 256, L"Main Window:%d", fps);

	SetWindowText(hwnd, wc);

	if (dev) {
		static FLOAT totalTime = 0;
		totalTime += timeInterval;

		D3DXMATRIX Rx, Ry;

		D3DXMatrixRotationX(&Rx, g_X);

		static FLOAT y = 0.0F;
		D3DXMatrixRotationY(&Ry, g_Y);

		D3DXMATRIX p = Rx * Ry;
		dev->SetTransform(D3DTS_WORLD, &p);

		dev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				   0xFF000000, 1.0F, 0);
		dev->BeginScene();

		dev->SetFVF(MyVertex::FVF);

		dev->SetStreamSource(0, vb, 0, sizeof(MyVertex));
		dev->SetIndices(ib);
		
		mesh->DrawSubset(0);

		dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

		dev->EndScene();
		dev->Present(0, 0, 0, 0);
	}
	return true;
}

VOID Clearup() {
	if (vb) {
		vb->Release();
		vb = NULL;
	}
	if (ib) {
		ib->Release();
		ib = NULL;
	}
	if (mesh) {
		mesh->Release();
		mesh = NULL;
	}
}

WPARAM MsgLoop(HWND hwnd, IDirect3DDevice9* dev, bool(*displayFunc)(HWND, IDirect3DDevice9*, FLOAT)) {
	MSG msg = {};

	FLOAT prevTime = (FLOAT)timeGetTime();
	FLOAT curTime;

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		} else {
			curTime = (FLOAT)timeGetTime();
			displayFunc(hwnd, dev, curTime - prevTime);
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
	d3dPresentParam->MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
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
	wndWidth = rect.right - rect.left;
	wndHeight = rect.bottom - rect.top;
	D3DPRESENT_PARAMETERS d3dParam;
	InitD3DParam(&d3dParam, hWnd, rect.right - rect.left, rect.bottom - rect.top, TRUE);

	HRESULT hResult = iDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
											   hWnd, behavoirFlag, &d3dParam, &device);
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
	Setup(device);

	MsgLoop(hWnd, device, DisplayFunc);

	End();

	Clearup();
	device->Release();

	return 0;
}

#endif //DRAGON_LESSON005_000