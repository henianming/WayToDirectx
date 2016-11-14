#include "program.h"
#include "Common/CommonCode.h"

HRESULT CALLBACK Program::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

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

	RETURN_IF_FAILED(ShowWindow(m_hWnd, showType));

	return TRUE;
}

BOOL Program::ReleaseWnd() {
	UnregisterClass(m_wndClass.lpszClassName, m_wndClass.hInstance);

	return TRUE;
}

BOOL Program::CreateDirectX() {
	return TRUE;
}

BOOL Program::ReleaseDirectX() {
	return TRUE;
}

Program::Program() {
	QueryPerformanceFrequency(&m_frequency);
}

BOOL Program::Create(HINSTANCE hInstance, int showType) {
	RETURN_IF_FAILED(CreateWnd(hInstance, showType));

	RETURN_IF_FAILED(CreateDirectX());

	return TRUE;
}

BOOL Program::Release() {
	RETURN_IF_FAILED(ReleaseDirectX());

	RETURN_IF_FAILED(ReleaseWnd());

	return TRUE;
}

BOOL Program::Update() {
	return TRUE;
}

double Program::GetCurTimeStamp() {
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return ((float)(count.QuadPart) / (float)(m_frequency.QuadPart));
}
