#include "lesson.h"
#ifdef CSDN_LESSON003

#include <d3dx9.h>

//窗口类名宏定义
#define WND_CLASS01 L"csdn_lesson003_001_class"
//窗口名宏定义
#define WND_NAME01 L"csdn_lesson003_001_wnd"

LPDIRECT3D9 d3dManager = NULL;
LPDIRECT3DDEVICE9 d3dDevice = NULL;
LPDIRECT3DVERTEXBUFFER9 d3dVertexBuf = NULL;

struct D3DVertexXYZRHW {
	float x, y, z, rhw;
	unsigned int color;
};

//自定函数声明
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

	//声明窗口类
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = WND_CLASS01;

	//注册窗口类
	if (!RegisterClassEx(&wc))
		return 0;

	//创建窗口，载入注册的窗口类
	HWND hwnd = CreateWindowEx(WS_EX_ACCEPTFILES, WND_CLASS01, WND_NAME01,
							   WS_CAPTION, posX, posY, posX + width, posY + height,
							   0, 0, hInstance, NULL);

	if (initializeD3D(hwnd)) {
		//将窗口设置为可见
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
	//创建一个d3d管理器
	d3dManager = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3dManager == NULL)
		return false;

	//创建一份d3d配置
	D3DPRESENT_PARAMETERS d3dCfg = {};
	d3dCfg.Windowed = TRUE;
	d3dCfg.BackBufferWidth = 1024;
	d3dCfg.BackBufferHeight = 768;
	d3dCfg.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DDISPLAYMODE displayMode;//用d3d管理器读取显示器显示模式
	if (FAILED(d3dManager->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
		return false;
	d3dCfg.BackBufferFormat = displayMode.Format;

	//用d3d管理器根据d3d配置创建一个d3d设备
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

	//渲染过程
	d3dDevice->BeginScene();//必须与EndScene()成对出现，指示GPU读取要渲染的数据
	/*
	  ... 渲染数据 ...
	  Draw(Box0);
	  Draw(Box1);
	  Draw(Box2);
	  Draw(Box3);
	*/
	//------------------------------------------------------------------------------------------
	d3dDevice->SetStreamSource(0, d3dVertexBuf, 0, sizeof(D3DVertexXYZRHW));//让设备载入顶点缓存
	d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);//设置设备的顶点数据结构
	d3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);//让设备根据其内的顶点缓存绘制图元
	//------------------------------------------------------------------------------------------
	d3dDevice->EndScene();//与BeginScene()成对出现，指示GPU停止读取渲染数据，并开始对已读取的数据进行计算渲染
	/*
	  ... CPU处理事项 ...
	  AI
	  逻辑
	*/
	d3dDevice->Present(NULL, NULL, NULL, NULL);//指示CPU从GPU读取渲染结果，并呈现  (此操作会等待GPU计算渲染完成才会返回，故不宜距离EndScene()过近，使CPU长期处于阻塞状态，以致失去CPU与GPU并发目的，浪费性能)
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
	//手动创建数组保存顶点数据
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

	//用D3D设备创建一个用于存放顶点数据的缓存
	if (FAILED(d3dDevice->CreateVertexBuffer(sizeof(vertexData), 0, D3DFVF_XYZRHW | D3DFVF_DIFFUSE,
											 D3DPOOL_DEFAULT, &d3dVertexBuf, NULL)))
		return false;

	//用ptr当媒介，向缓存填入顶点数据
	void *ptr;
	if (FAILED(d3dVertexBuf->Lock(0, sizeof(vertexData), (void**)&ptr, 0)))
		return false;
	memcpy(ptr, vertexData, sizeof(vertexData));
	d3dVertexBuf->Unlock();

	return true;
}

#endif