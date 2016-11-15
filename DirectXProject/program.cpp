#include "program.h"
#include "Common/CommonCode.h"

void Program::InitWndClass(HINSTANCE hInstance) {
	m_wndClass.cbClsExtra = 0;
	m_wndClass.cbWndExtra = 0;
	m_wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	m_wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_wndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	m_wndClass.hInstance = hInstance;
	m_wndClass.lpfnWndProc = WndProc;
	m_wndClass.lpszClassName = L"DirectX Program Class";
	m_wndClass.lpszMenuName = NULL;
	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
}

BOOL Program::CreateWnd(HINSTANCE hInstance, int showType) {
	InitWndClass(hInstance);

	RegisterClass(&m_wndClass);

	m_hWnd = CreateWindow(
		m_wndClass.lpszClassName, L"DirectX Program Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 450,
		0, 0, m_wndClass.hInstance, 0
		);
	if (m_hWnd == 0) {
		return FALSE;
	}

	ShowWindow(m_hWnd, showType);

	return TRUE;
}

BOOL Program::ReleaseWnd() {
	UnregisterClass(m_wndClass.lpszClassName, m_wndClass.hInstance);

	return TRUE;
}

void Program::InitDirectPresentParameters() {
	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	LONG w = rect.right - rect.left;
	LONG h = rect.bottom - rect.top;

	m_d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dPresentParameters.BackBufferCount = 2;
	m_d3dPresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_d3dPresentParameters.BackBufferHeight = h;
	m_d3dPresentParameters.BackBufferWidth = w;
	m_d3dPresentParameters.EnableAutoDepthStencil = TRUE;
	m_d3dPresentParameters.Flags = 0;
	m_d3dPresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dPresentParameters.hDeviceWindow = m_hWnd;
	m_d3dPresentParameters.MultiSampleQuality = 0;
	m_d3dPresentParameters.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	m_d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dPresentParameters.Windowed = TRUE;
}

BOOL Program::CreateDirectX() {
	HRESULT hResult;

	m_iDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_iDirect3D9 == NULL) {
		return FALSE;
	};

	InitDirectPresentParameters();

	D3DCAPS9 d3dCaps9;
	hResult = m_iDirect3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps9);
	if (FAILED(hResult)) {
		return FALSE;
	}
	DWORD behaviorFlags;
	if (d3dCaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		behaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		behaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	hResult = m_iDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, behaviorFlags, &m_d3dPresentParameters, &m_device);
	if (FAILED(hResult)) {
		return FALSE;
	}

	return TRUE;
}

BOOL Program::ReleaseDirectX() {
	if (m_device) {
		m_device->Release();
		m_device = NULL;
	}

	if (m_iDirect3D9) {
		m_iDirect3D9->Release();
		m_iDirect3D9 = NULL;
	}

	return TRUE;
}

Program::Program() {
	QueryPerformanceFrequency(&m_frequency);
}

BOOL Program::Create(HINSTANCE hInstance, int showType) {
	RETURN_IF_FAILED(m_wndProcEventMgr.Create());

	RETURN_IF_FAILED(CreateWnd(hInstance, showType));

	RETURN_IF_FAILED(CreateDirectX());

	return TRUE;
}

BOOL Program::Release() {
	RETURN_IF_FAILED(ReleaseDirectX());

	RETURN_IF_FAILED(ReleaseWnd());

	RETURN_IF_FAILED(m_wndProcEventMgr.Release());

	return TRUE;
}

BOOL Program::Update() {
	return TRUE;
}

WndProcEventMgr* Program::GetWndProcEventMgr() {
	return &m_wndProcEventMgr;
}

double Program::GetCurTimeStamp() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return ((float)(count.QuadPart) / (float)(m_frequency.QuadPart));
}
