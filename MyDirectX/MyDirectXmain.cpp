#include "../lesson.h"
#ifdef MyDirectX

#include <windows.h>
#include "directx_window.h"

WPARAM MsgLoop(DirectXWindow *directXWindow) {
	MSG msg = {};

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		} else {
			if (directXWindow == NULL) {
				continue;
			}

			directXWindow->displayFunc(NULL);
		}
	}

	return msg.wParam;
}

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR argv, INT showType) {
	DirectXWindow dxWnd(hInstance, L"DirectX Wnd Class", L"DirectX Window");

	dxWnd.CreateWnd();

	dxWnd.CreateDirectX();

	dxWnd.ShowWnd(showType);

	MsgLoop(&dxWnd);

	dxWnd.ReleaseDirectX();

	dxWnd.ReleaseWnd();

	return 0;
}

#endif //MyDirectX