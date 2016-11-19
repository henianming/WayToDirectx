#ifndef COMMON_CODE_H
#define COMMON_CODE_H

#include <Windows.h>
#include <d3d9.h>

#define SAFEDELETE(a) \
do{ \
	if (a) { \
		delete (a); \
	} \
}while(0) \

#define SAFEDELETENULL(a) \
do{ \
	if (a) { \
		delete (a); \
		(a) = NULL; \
	} \
}while(0) \

#define UNUSED(a) ((void)(a))

#define RETURN_IF_FAILED(A) \
do { \
	if (!A) { \
		return FALSE; \
	} \
} while(0) \

class XYZCVertex {
public:
	static DWORD const FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

public:
	float m_x, m_y, m_z;
	D3DCOLOR m_color;

public:
	XYZCVertex(float x, float y, float z, D3DCOLOR color);
};

#endif //COMMON_CODE_H
