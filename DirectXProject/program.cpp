#include "program.h"

void Program::InitWndClass() {
	m_wndClass.cbClsExtra = 0;
	m_wndClass.cbWndExtra = 0;
	m_wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	m_wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_wndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	m_wndClass.hInstance = m_hInstance;
	m_wndClass.lpfnWndProc = 
}

BOOL Program::Create(HINSTANCE hInstance) {
	m_hInstance = hInstance;
}

BOOL Program::Release() {

}

BOOL Program::DataUpdate() {
	return TRUE;
}

BOOL Program::DisplayUpdate() {
	return TRUE;
}