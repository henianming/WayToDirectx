#include "lesson.h"
#ifdef DRAGON_LESSON001_003

#include <d3d9.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	if (false) {
		IDirect3DSurface9 *surface; //生成一个表面类型surface，此为测试代码，未分配内存

		//获取该表面的信息，保存到desc中
		//Width保存了表面的宽度，以像素为单位，忽略最后的缓存区的空间
		//Height保存了表面的高度，以像素为单位
		D3DSURFACE_DESC desc;
		surface->GetDesc(&desc);

		//锁住该表面的像素信息，保存到rect中
		//Pitch保存了表面的像素一行的数据长度，以字节为单位
		//pBits保存了表面的像素的数据矩阵的指针，指针指向的4字节空间保存了像素的颜色信息
		D3DLOCKED_RECT rect;
		surface->LockRect(&rect, 0, 0);
		{
			DWORD *imageData = (DWORD*)rect.pBits;
			for (UINT i = 0; i < desc.Height; i++) {
				for (UINT j = 0; j < desc.Width; j++) {
					//因Pitch以字节为单位，pBits以DWORD的4字节长度为跨度当索引，故Pitch需要除以4来当索引用
					int index = i*rect.Pitch / 4 + j;
					imageData[index] = 0xFFFF0000;
				}
			}
		}
		surface->UnlockRect();
	}

	//多重采样级别枚举
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
	//IDirect3D9::CheckDeviceMultiSampleType该方法检测当前是否支持所给多重采样级别

	//像素格式枚举
	D3DFORMAT d3dFormat;
	d3dFormat = D3DFMT_R8G8B8;
	d3dFormat = D3DFMT_A8R8G8B8;
	d3dFormat = D3DFMT_X8R8G8B8;
	d3dFormat = D3DFMT_A16B16G16R16F;
	d3dFormat = D3DFMT_A32B32G32R32F;

	//内存池枚举
	D3DPOOL d3dPool;
	d3dPool = D3DPOOL_DEFAULT;
	d3dPool = D3DPOOL_MANAGED;
	d3dPool = D3DPOOL_SYSTEMMEM;
	d3dPool = D3DPOOL_SCRATCH;
	d3dPool = D3DPOOL_FORCE_DWORD;

	//交换链
	IDirect3DSwapChain9 *swapChain;

	//深度缓存格式枚举
	d3dFormat = D3DFMT_D32;
	d3dFormat = D3DFMT_D24S8;
	d3dFormat = D3DFMT_D24X8;
	d3dFormat = D3DFMT_D24X4S4;
	d3dFormat = D3DFMT_D16;

	//检查设备是否支持某一个功能(例如硬件顶点运算)
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