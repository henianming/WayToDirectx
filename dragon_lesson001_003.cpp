#include "lesson.h"
#ifdef DRAGON_LESSON001_003

#include <d3d9.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	if (false) {
		IDirect3DSurface9 *surface; //����һ����������surface����Ϊ���Դ��룬δ�����ڴ�

		//��ȡ�ñ������Ϣ�����浽desc��
		//Width�����˱���Ŀ�ȣ�������Ϊ��λ���������Ļ������Ŀռ�
		//Height�����˱���ĸ߶ȣ�������Ϊ��λ
		D3DSURFACE_DESC desc;
		surface->GetDesc(&desc);

		//��ס�ñ����������Ϣ�����浽rect��
		//Pitch�����˱��������һ�е����ݳ��ȣ����ֽ�Ϊ��λ
		//pBits�����˱�������ص����ݾ����ָ�룬ָ��ָ���4�ֽڿռ䱣�������ص���ɫ��Ϣ
		D3DLOCKED_RECT rect;
		surface->LockRect(&rect, 0, 0);
		{
			DWORD *imageData = (DWORD*)rect.pBits;
			for (UINT i = 0; i < desc.Height; i++) {
				for (UINT j = 0; j < desc.Width; j++) {
					//��Pitch���ֽ�Ϊ��λ��pBits��DWORD��4�ֽڳ���Ϊ��ȵ���������Pitch��Ҫ����4����������
					int index = i*rect.Pitch / 4 + j;
					imageData[index] = 0xFFFF0000;
				}
			}
		}
		surface->UnlockRect();
	}

	//���ز�������ö��
	D3DMULTISAMPLE_TYPE d3dMultiSample_Type;
	d3dMultiSample_Type = D3DMULTISAMPLE_NONE;
	d3dMultiSample_Type = D3DMULTISAMPLE_NONMASKABLE;
	d3dMultiSample_Type = D3DMULTISAMPLE_2_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_3_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_4_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_5_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_6_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_7_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_8_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_9_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_10_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_11_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_12_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_13_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_14_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_15_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_16_SAMPLES;
	d3dMultiSample_Type = D3DMULTISAMPLE_FORCE_DWORD;
	//IDirect3D9::CheckDeviceMultiSampleType�÷�����⵱ǰ�Ƿ�֧���������ز�������

	//���ظ�ʽö��
	D3DFORMAT d3dFormat;
	d3dFormat = D3DFMT_R8G8B8;
	d3dFormat = D3DFMT_A8R8G8B8;
	d3dFormat = D3DFMT_X8R8G8B8;
	d3dFormat = D3DFMT_A16B16G16R16F;
	d3dFormat = D3DFMT_A32B32G32R32F;

	//�ڴ��ö��
	D3DPOOL d3dPool;
	d3dPool = D3DPOOL_DEFAULT;
	d3dPool = D3DPOOL_MANAGED;
	d3dPool = D3DPOOL_SYSTEMMEM;
	d3dPool = D3DPOOL_SCRATCH;
	d3dPool = D3DPOOL_FORCE_DWORD;

	//������
	IDirect3DSwapChain9 *swapChain;

	//��Ȼ����ʽö��
	d3dFormat = D3DFMT_D32;
	d3dFormat = D3DFMT_D24S8;
	d3dFormat = D3DFMT_D24X8;
	d3dFormat = D3DFMT_D24X4S4;
	d3dFormat = D3DFMT_D16;

	//����豸�Ƿ�֧��ĳһ������(����Ӳ����������)
	bool bSupportsHardwareVertexProcessing;
	D3DCAPS9 caps;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		bSupportsHardwareVertexProcessing = true;
	} else {
		bSupportsHardwareVertexProcessing = false;
	}

	while (1);
	return 0;
}

#endif // DRAGON_LESSON001_003