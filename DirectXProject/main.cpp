#include "../lesson.h"
#ifdef DirectXProject

#include <Windows.h>
#include "program.h"

Program *g_program;

HRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (g_program) {
		if (!(g_program->GetWndProcEventMgr()->FireEvent())) {
			return DefWindowProc(hWnd, msg, wParam, lParam);
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