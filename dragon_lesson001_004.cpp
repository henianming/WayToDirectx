#include "lesson.h"
#ifdef DRAGON_LESSON001_004

#include <d3d9.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	HWND hwnd; //������

	//IDirect3D��ʼ���Ĳ���
	//1.��ȡָ��ӿ�IDirect3D9��ָ��
	IDirect3D9 *iDirect3d9; //�ýӿ���Ҫ��;���豸ö�١���������IDirect3DDevice9���͵Ķ���
	iDirect3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	//2.У��Ӳ������(��Ӳ����������Ϊ��)
	D3DCAPS9 d3dCaps9;
	iDirect3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps9);
	int vp = 0;
	if (d3dCaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//3.���D3DPRESENT_PARAMETERS�ṹ
	D3DPRESENT_PARAMETERS d3dPresent_Parameters;
	d3dPresent_Parameters.BackBufferWidth = 800;
	d3dPresent_Parameters.BackBufferHeight = 600;
	d3dPresent_Parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dPresent_Parameters.BackBufferCount = 1;
	d3dPresent_Parameters.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	d3dPresent_Parameters.MultiSampleQuality = 0;
	d3dPresent_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPresent_Parameters.hDeviceWindow = hwnd;
	d3dPresent_Parameters.Windowed = TRUE;
	d3dPresent_Parameters.EnableAutoDepthStencil = TRUE;
	d3dPresent_Parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dPresent_Parameters.Flags = 0; //
	d3dPresent_Parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//4.����IDirect3DDevice9�ӿ�
	IDirect3DDevice9 *iDirect3DDevice9;
	HRESULT hResult = iDirect3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dPresent_Parameters, &iDirect3DDevice9);
	if (FAILED(hResult)) {
		//ʧ��
	} else {
		//�ɹ�
	}

	while (1);
	return 0;
}

#endif // DRAGON_LESSON001_004