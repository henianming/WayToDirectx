#include "lesson.h"
#ifdef DRAGON_LESSON001_001

#include <d3d9.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow) {
	//D3D设备种类枚举
	D3DDEVTYPE d3dDevType;
	d3dDevType = D3DDEVTYPE_HAL; //硬件设备
	d3dDevType = D3DDEVTYPE_REF; //参考光栅设备
	d3dDevType = D3DDEVTYPE_SW;
	d3dDevType = D3DDEVTYPE_NULLREF;
	d3dDevType = D3DDEVTYPE_FORCE_DWORD;
	
	while (1);
	return 0;
}

#endif // DRAGON_LESSON001_001