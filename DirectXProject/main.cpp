#include "../lesson.h"
#ifdef DirectXProject

#include <windows.h>
#include "program.h"

Program *g_program;
BOOL g_isDataRunning = TRUE;

HANDLE g_displayHandle;
BOOL g_isDisplayRunning = TRUE;

WPARAM MsgLoop() {
	MSG msg = {};
	while (g_isDisplayRunning && msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		} else {
			g_program->DataUpdate();
		}
	}

	g_isDataRunning = FALSE;

	if (msg.message != WM_QUIT) {
		return 0;
	} else {
		return msg.wParam;
	}
}

DWORD APIENTRY DisplayLoop(LPVOID argv) {
	while (g_isDataRunning && g_program->DisplayUpdate()) {

	}

	g_isDisplayRunning = FALSE;

	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR argv, int showType) {
	g_program = new Program();

	g_program->Create(hInstance);

	WPARAM wParam = MsgLoop();
	g_displayHandle = CreateThread(NULL, 0, DisplayLoop, NULL, 0, NULL);

	g_program->Release();

	delete g_program;

	return wParam;
}

#endif //DirectXProject