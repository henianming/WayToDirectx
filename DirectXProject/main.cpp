#include "../lesson.h"
#ifdef DirectXProject

#include <Windows.h>
#include "program.h"

HProgram *g_program;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (g_program) {
		switch (msg) {
		case WM_KEYDOWN:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_KEYDOWN, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_KEYUP:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_KEYUP, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_LBUTTONDOWN:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_LBUTTONDOWN, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_RBUTTONDOWN:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_RBUTTONDOWN, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_MOUSEMOVE:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_MOUSEMOVE, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_LBUTTONUP:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_LBUTTONUP, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_RBUTTONUP:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_RBUTTONUP, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_MOVE:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_MOVE, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_MOVING:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_MOVING, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_SIZE:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_SIZE, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_SIZING:
		{
			if (g_program->Get_m_wndProcEventMgr()->FireEvent(HWndProcEventType_SIZING, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}break;
		}
	}
	if (wParam == 304 && lParam == 17817868) {
		INT ii = 333;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

WPARAM MsgLoop() {
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		} else {
			g_program->Update();
		}
	}
	return msg.wParam;
}

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR argv, INT showType) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	HWND hWnd = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);

	g_program = new HProgram();

	g_program->Create(hInstance, showType);

	WPARAM wParam = MsgLoop();

	g_program->Release();

	delete g_program;

	return wParam;
}

#endif //DirectXProject