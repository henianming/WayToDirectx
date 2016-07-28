#include "lesson.h"
#ifdef DRAGON_LESSON_EXTRA

#include <windows.h>

/*------------------------------------------------------------------------------
hWnd:该消息所属窗口
msg:消息的ID
wParam:消息的参数，内容由消息ID决定，具体需查阅MSDN
lParam:消息的参数，内容由消息ID决定，具体需查阅MSDN
------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_KEYUP: //虚拟按键消息，总为大写
		switch (wParam) {
		case 'A':
			MessageBox(hWnd, L"WM_KEYUP", L"msg", MB_OK);
			break;
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_CHAR: //翻译后的字符消息，是否大写由输入决定
		switch (wParam) {
		case 'b':
			MessageBox(hWnd, L"WM_CHAR", L"msg", MB_OK);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*------------------------------------------------------------------------------
hInstance:当前应用程序实例的句柄
hInstancePrev:在32位的Win32编程中，不使用该参数，设置为0
lpCmdLine:运行该程序时，命令行里所输入的字符串
nCmdShow:指定应用程序窗口的显示形式
         SW_SHOWDEFAULT:以默认形式显示
		 SW_SHOWMINIMIZED:以最小化运行
		 SW_SHOWMAXIMIZED:以最大化运行
------------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	//定义一个窗口类，以下必须全部指定明确的值
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"class name";
	wc.lpszMenuName = 0;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	//注册这个窗口类
	if (!RegisterClass(&wc)) {
		MessageBox(0, L"RegisterClass Failed!", L"Error", MB_OK);
		return 0;
	}

	//按照这个窗口类创建一个窗口
	HWND hWnd = CreateWindow(L"class name", L"test window",
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
							 0, 0, hInstance, 0);

	//显示这个窗口
	ShowWindow(hWnd, nCmdShow);

	//消息循环
	int ret;
	MSG msg;
	//从系统捕获消息，只要不是捕获的QUIT信号，均返回非0值
	if (false) {
		while ((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
			if (ret == -1) { //返回-1，表示消息出错了
				MessageBox(0, L"Message Error!", L"Error", MB_OK);
			} else { //正常
				//翻译虚拟按键消息为字符按键
				TranslateMessage(&msg);
				//把捕获的消息发送到对应的窗口过程
				DispatchMessage(&msg);
			}
		}
	} else {
		while (true) {
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				if (msg.message == WM_QUIT) {
					return 0;
				}
			}
		}
	}

	return 0;
}

#endif // DRAGON_LESSON_EXTRA