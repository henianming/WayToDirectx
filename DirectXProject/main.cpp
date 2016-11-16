#include "../lesson.h"
#ifdef DirectXProject

#include <Windows.h>
#include "program.h"

Program *g_program;

HRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (g_program) {
		switch (msg) {
		case WM_KEYDOWN:
		{
			if (g_program->GetWndProcEventMgr()->FireEvent(EventType_KeyDown, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_KEYUP:
		{
			if (g_program->GetWndProcEventMgr()->FireEvent(EventType_KeyUp, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_LBUTTONDOWN:
		{
			if (g_program->GetWndProcEventMgr()->FireEvent(EventType_LBUTTONDOWN, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_RBUTTONDOWN:
		{
			if (g_program->GetWndProcEventMgr()->FireEvent(EventType_RBUTTONDOWN, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_MOUSEMOVE:
		{
			if (g_program->GetWndProcEventMgr()->FireEvent(EventType_MOUSEMOVE, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_LBUTTONUP:
		{
			if (g_program->GetWndProcEventMgr()->FireEvent(EventType_LBUTTONUP, wParam, lParam)) {
				return 0;
			}
		}break;
		case WM_RBUTTONUP:
		{
			if (g_program->GetWndProcEventMgr()->FireEvent(EventType_RBUTTONUP, wParam, lParam)) {
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

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR argv, int showType) {
	g_program = new Program();

	g_program->Create(hInstance, showType);

	WPARAM wParam = MsgLoop();

	g_program->Release();

	delete g_program;

	return wParam;
}

#endif //DirectXProject