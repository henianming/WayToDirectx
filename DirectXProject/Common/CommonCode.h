#pragma once

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

#define UNUSED(a) ((VOID)(a))

#define RETURN_IF_FAILED(A) \
do { \
	if (!A) { \
		return FALSE; \
	} \
} while(0) \

#define RETURN_IF_NULL(A) \
do { \
	if ((A) == NULL) { \
		return FALSE; \
	} \
} while(0) \

#define IS_IN_RANGE_LN_HN(S, L, H) ((S) > (L) && (S) < (H)) ? TRUE : FALSE
#define IS_IN_RANGE_LE_HE(S, L, H) ((S) >= (L) && (S) <= (H)) ? TRUE : FALSE
#define IS_IN_RANGE_LE_HN(S, L, H) ((S) >= (L) && (S) < (H)) ? TRUE : FALSE
#define IS_IN_RANGE_LN_HE(S, L, H) ((S) > (L) && (S) <= (H)) ? TRUE : FALSE

#define ABS(N) ((N) > 0) ? N : (0 - N)

//--------·Ö½çÏß-----------------------------------------------------------------
class HXYZCVertex {
public:
	static DWORD const FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

public:
	FLOAT m_x, m_y, m_z;
	D3DCOLOR m_color;

public:
	HXYZCVertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color);
};
