#include "lesson.h"
#ifdef CSDN_LESSON002

#include <d3dx9.h>

//���������궨��
#define WND_CLASS01 L"csdn_lesson002_001_class"
//�������궨��
#define WND_NAME01 L"csdn_lesson002_001_wnd"

LPDIRECT3D9 d3dManager = NULL;
LPDIRECT3DDEVICE9 d3dDevice = NULL;

//�Զ���������
LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool initializeD3D(HWND hwnd);
void renderScene();
void shutDown();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow) {
	int posX = 25;
	int posY = 25;
	unsigned int width = 1024;
	unsigned int height = 768;

	//����������
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = WND_CLASS01;

	//ע�ᴰ����
	if (!RegisterClassEx(&wc))
		return 0;

	//�������ڣ�����ע��Ĵ�����
	HWND hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, WND_CLASS01, WND_NAME01,
							   WS_CAPTION, posX, posY, posX + width, posY + height,
							   0, 0, hInstance, NULL);

	if (initializeD3D(hwnd)) {
		//����������Ϊ�ɼ�
		ShowWindow(hwnd, nCmdShow);
	}

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			renderScene();
		}
	}

	shutDown();
	UnregisterClass(WND_CLASS01, hInstance);

	return 0;
}

LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_KEYUP:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		default:
			return 0;
		}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

bool initializeD3D(HWND hwnd) {
	//����һ��d3d������
	d3dManager = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3dManager == NULL)
		return false;

	//����һ��d3d����
	D3DPRESENT_PARAMETERS d3dCfg = {};
	d3dCfg.Windowed = TRUE;
	d3dCfg.BackBufferWidth = 1024;
	d3dCfg.BackBufferHeight = 768;
	d3dCfg.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DDISPLAYMODE displayMode;//��d3d��������ȡ��ʾ����ʾģʽ
	if (FAILED(d3dManager->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		return false;
	d3dCfg.BackBufferFormat = displayMode.Format;

	//��d3d����������d3d���ô���һ��d3d�豸
	if (FAILED(d3dManager->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
										hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&d3dCfg, &d3dDevice)))
		return false;

	return true;
}

void renderScene() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(1, 0, 0, 0), 1.0f, 0);

	//��Ⱦ����
	d3dDevice->BeginScene();//������EndScene()�ɶԳ��֣�ָʾGPU��ȡҪ��Ⱦ������
	/*
	  ... ��Ⱦ���� ...
	  Draw(Box0);
	  Draw(Box1);
	  Draw(Box2);
	  Draw(Box3);
	*/
	d3dDevice->EndScene();//��BeginScene()�ɶԳ��֣�ָʾGPUֹͣ��ȡ��Ⱦ���ݣ�����ʼ���Ѷ�ȡ�����ݽ��м�����Ⱦ
	/*
	  ... CPU�������� ...
	  AI
	  �߼�
	*/
	d3dDevice->Present(NULL, NULL, NULL, NULL);//ָʾCPU��GPU��ȡ��Ⱦ�����������  (�˲�����ȴ�GPU������Ⱦ��ɲŻ᷵�أ��ʲ��˾���EndScene()������ʹCPU���ڴ�������״̬������ʧȥCPU��GPU����Ŀ�ģ��˷�����)
}

void shutDown() {
	if (d3dDevice != NULL) {
		d3dDevice->Release();
		d3dDevice = NULL;
	}

	if (d3dManager != NULL) {
		d3dManager->Release();
		d3dManager = NULL;
	}
}

#endif