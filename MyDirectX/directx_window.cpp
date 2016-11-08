#include "directx_window.h"

DirectXWindow::ObjMap DirectXWindow::sm_objMap;

LRESULT CALLBACK DirectXWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	ObjIt it = sm_objMap.find(hWnd);
	if (it == sm_objMap.end()) {
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return it->second->ObjWndProc(msg, wParam, lParam);
}

DirectXWindow::DirectXWindow(HINSTANCE hInstance, LPCWSTR className, LPCWSTR wndName)
	: m_wndName(wndName) {
	m_wndClass.hInstance = hInstance;
	m_wndClass.lpszClassName = className;
}

DirectXWindow::~DirectXWindow() {
	
}

BOOL DirectXWindow::CreateWnd() {
	InitWndClass();

	if (!RegisterClass(&m_wndClass)) {
		return FALSE;
	}

	m_hWnd = CreateWindow(m_wndClass.lpszClassName, m_wndName,
						  WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
						  0, 0, m_wndClass.hInstance, 0);
	if (m_hWnd == NULL) {
		return FALSE;
	}

	sm_objMap.insert(ObjPair(m_hWnd, this));

	return TRUE;
}

BOOL DirectXWindow::ReleaseWnd() {
	ObjIt it = sm_objMap.find(m_hWnd);
	if (it != sm_objMap.end()) {
		sm_objMap.erase(m_hWnd);
	}

	if (!DestroyWindow(m_hWnd)) {
		return FALSE;
	}

	if (!UnregisterClass(m_wndClass.lpszClassName, m_wndClass.hInstance)) {
		return FALSE;
	}

	return TRUE;
}

BOOL DirectXWindow::CreateDirectX() {
	m_iDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_iDirect3D9) {
		return FALSE;
	}

	m_iDirect3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_d3dCaps9);
	DWORD BehaviorFlags;
	if (m_d3dCaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		BehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		BehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	InitD3DPresentParameters();

	HRESULT hResult = m_iDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, BehaviorFlags, &m_d3dPresentParameters, &m_device);
	if (FAILED(hResult)) {
		return FALSE;
	}

	m_graphicObject = new Graphic3();
	m_graphicObject->Load(m_hWnd, m_device);
	m_graphicObject->Show();

	return TRUE;
}

BOOL DirectXWindow::ReleaseDirectX() {
	if (m_graphicObject) {
		m_graphicObject->Hide();
		m_graphicObject->Unload();
		delete m_graphicObject;
		m_graphicObject = NULL;
	}

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

BOOL DirectXWindow::ShowWnd(int showType) {
	return ShowWindow(m_hWnd, showType);
}

LRESULT DirectXWindow::ObjWndProc(UINT msg, WPARAM wParam, LPARAM lParam) {
	if (m_graphicObject->OnMessage(msg, wParam, lParam)) {
		return 0;
	}
	return DefWindowProc(m_hWnd, msg, wParam, lParam);
}

void DirectXWindow::displayFunc(void *data) {
	m_graphicObject->Update(data);
}

void DirectXWindow::InitWndClass() {
	m_wndClass.cbClsExtra = 0;
	m_wndClass.cbWndExtra = 0;
	m_wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	m_wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_wndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	m_wndClass.lpfnWndProc = WndProc;
	m_wndClass.lpszMenuName = 0;
	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
}

void DirectXWindow::InitD3DPresentParameters() {
	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	LONG w = rect.right - rect.left;
	LONG h = rect.bottom - rect.top;

	m_d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dPresentParameters.BackBufferCount = 2;
	m_d3dPresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_d3dPresentParameters.BackBufferHeight = w;
	m_d3dPresentParameters.BackBufferWidth = h;
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
