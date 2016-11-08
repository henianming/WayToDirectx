#include "graphic4.h"

MyVertex4::MyVertex4(float x, float y, float z, D3DCOLOR color)
	: m_x(x), m_y(y), m_z(z), m_color(color) {
}

Graphic4::Graphic4() {

}

Graphic4::~Graphic4() {

}

BOOL Graphic4::Load(HWND hWnd, IDirect3DDevice9 *device) {
	m_hWnd = hWnd;
	m_device = device;

	return TRUE;
}

BOOL Graphic4::Unload() {
	return TRUE;
}

BOOL Graphic4::Show() {
	return TRUE;
}

BOOL Graphic4::Hide() {
	return TRUE;
}

BOOL Graphic4::Update(void *data) {
	return TRUE;
}

BOOL Graphic4::OnMessage(UINT msg, WPARAM wParam, LPARAM lParam) {
	return FALSE;
}
