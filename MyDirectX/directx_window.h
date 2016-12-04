#pragma once

#include <d3d9.h>
#include <map>
#include "i_graphic_object.h"
#include "graphic3.h"
#include "graphic4.h"

class DirectXWindow {
	typedef std::map<HWND, DirectXWindow*> ObjMap;
	typedef std::map<HWND, DirectXWindow*>::iterator ObjIt;
	typedef std::pair<HWND, DirectXWindow*> ObjPair;
private:
	static ObjMap sm_objMap;

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	LPCWSTR m_wndName;
	WNDCLASS m_wndClass;
	HWND m_hWnd;

	IDirect3D9 *m_iDirect3D9;
	IDirect3DDevice9 *m_device;
	D3DCAPS9 m_d3dCaps9;
	D3DPRESENT_PARAMETERS m_d3dPresentParameters;

	IGraphicObject *m_graphicObject;

public:
	DirectXWindow(HINSTANCE hInstance, LPCWSTR className, LPCWSTR wndName);
	~DirectXWindow();

	BOOL CreateWnd();
	BOOL ReleaseWnd();
	BOOL CreateDirectX();
	BOOL ReleaseDirectX();
	BOOL ShowWnd(int showType);

	LRESULT ObjWndProc(UINT msg, WPARAM wParam, LPARAM lParam);
	void displayFunc(void *data);

private:
	void InitWndClass();
	void InitD3DPresentParameters();
};