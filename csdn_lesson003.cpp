#include "lesson.h"
#ifdef CSDN_LESSON003

#include <d3dx9.h>

//���������궨��
#define WND_CLASS01 L"csdn_lesson003_001_class"
//�������궨��
#define WND_NAME01 L"csdn_lesson003_001_wnd"

LPDIRECT3D9 d3dManager = NULL;
LPDIRECT3DDEVICE9 d3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 d3dVertexBuf = NULL;

struct D3DVertexXYZRHW {
	float x, y, z, rhw;
	unsigned int color;
};

//�Զ���������
LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
bool initializeD3D(HWND hwnd);
void renderScene();
void shutDown();
bool initializeObj();

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

		MSG msg = {};
		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				renderScene();
			}
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

	if (!initializeObj())
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
	//------------------------------------------------------------------------------------------
	d3dDevice->SetStreamSource(0, d3dVertexBuf, 0, sizeof(D3DVertexXYZRHW));//���豸���붥�㻺��
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);//�����豸�Ķ������ݽṹ
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);//���豸�������ڵĶ��㻺�����ͼԪ
	//------------------------------------------------------------------------------------------
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

	if (d3dVertexBuf != NULL) {
		d3dVertexBuf->Release();
		d3dVertexBuf = NULL;
	}
}

bool initializeObj() {
	//�ֶ��������鱣�涥������
	unsigned int colorInfo = D3DCOLOR_ARGB(1, 255, 255, 255);
	D3DVertexXYZRHW vertexData[] =
	{
		{ 10.0f, 10.0f, 0.0f, 1.0f, colorInfo },
		{ 200.0f, 10.0f, 0.0f, 1.0f, colorInfo },
		{ 10.0f, 200.0f, 0.0f, 1.0f, D3DCOLOR_ARGB(1, 0, 0, 0) },
		{ 200.0f, 200.0f, 0.0f, 1.0f, colorInfo },
		{ 400.0f, 200.0f, 0.0f, 1.0f, colorInfo },
		{ 200.0f, 400.0f, 0.0f, 1.0f, colorInfo },
	};

	//��D3D�豸����һ�����ڴ�Ŷ������ݵĻ���
	if (FAILED(d3dDevice->CreateVertexBuffer(sizeof(vertexData), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
											 D3DPOOL_DEFAULT, &d3dVertexBuf, NULL)))
		return false;

	//��ptr��ý�飬�򻺴����붥������
	void *ptr;
	if (FAILED(d3dVertexBuf->Lock(0, sizeof(vertexData), (void**)&ptr, 0)))
		return false;
	memcpy(ptr, vertexData, sizeof(vertexData));
	d3dVertexBuf->Unlock();

	return true;
}

#endif