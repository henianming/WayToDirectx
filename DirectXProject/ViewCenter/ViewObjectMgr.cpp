#include "ViewObjectMgr.h"

#include "ViewObject/InitialViewObject.h"
#include "Common/CommonCode.h"
#include "program.h"

extern Program *g_program;

HIViewObject::~HIViewObject() {
	//clear child
	std::list<HIViewObject*>::iterator it = m_childViewObjectList.begin();
	while (it != m_childViewObjectList.end()) {
		delete (*it);

		it++;
	}

	Hide();
	Unload();
	UnsetParentViewObject();

	//clear self data
}

void HIViewObject::SetParentViewObject(HIViewObject *parent, BOOL isOtherCall) {
	if (m_parentViewObject != NULL) {
		UnsetParentViewObject();
	}

	m_parentViewObject = parent;
	if (isOtherCall == TRUE) {
		m_parentViewObject->AddChildViewObject(this, FALSE);
	}
}

void HIViewObject::UnsetParentViewObject(BOOL isOtherCall) {
	if (m_parentViewObject == NULL) {
		return;
	}

	if (isOtherCall == TRUE) {
		m_parentViewObject->DelChildViewObject(this, FALSE);
	}
	m_parentViewObject = NULL;
}

void HIViewObject::AddChildViewObject(HIViewObject *child, BOOL isOtherCall) {
	if (child == NULL) {
		return;
	}

	m_childViewObjectList.push_back(child);
	if (isOtherCall == TRUE) {
		child->SetParentViewObject(this, FALSE);
	}
}

void HIViewObject::DelChildViewObject(HIViewObject *child, BOOL isOtherCall) {
	std::list<HIViewObject*>::iterator it = m_childViewObjectList.begin();
	while (it != m_childViewObjectList.end()) {
		if ((int)(*it) == (int)child) {
			if (isOtherCall == TRUE) {
				(*it)->UnsetParentViewObject(FALSE);
			}
			m_childViewObjectList.erase(it);
			return;
		}

		it++;
	}
}

void HIViewObject::UpdateChile() {
	std::list<HIViewObject*>::iterator it = m_childViewObjectList.begin();
	while (it != m_childViewObjectList.end()) {
		(*it)->Update();
		(*it)->UpdateChile();
		it++;
	}
}

void HIViewObject::Update() {

}

ViewObjectMgr::ViewObjectMgr()
	:m_cameraSpeed(1.0f) {

}

BOOL ViewObjectMgr::Create() {
	m_eye = D3DXVECTOR3(1.0f, 1.0f, -5.0f);
	m_target = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	IDirect3DDevice9 *device = g_program->Get_m_device();
	RECT rect;
	GetWindowRect(g_program->Get_m_hWnd(), &rect);
	LONG w = rect.right - rect.left;
	LONG h = rect.bottom - rect.top;
	D3DXMATRIX perspective;
	D3DXMatrixPerspectiveFovLH(
		&perspective,
		D3DX_PI * 0.5,
		(float)w / (float)h,
		0.0f,
		1000.0f
	);
	device->SetTransform(D3DTS_PROJECTION, &perspective);

	m_rootViewObject = new InitialViewObject();
	m_rootViewObject->Load();
	m_rootViewObject->Show();

	return TRUE;
}

BOOL ViewObjectMgr::Release() {
	m_rootViewObject->Hide();
	m_rootViewObject->Unload();
	SAFEDELETENULL(m_rootViewObject);

	return TRUE;
}

void ViewObjectMgr::Update() {
	IDirect3DDevice9 *device = g_program->Get_m_device();
	D3DXMATRIX camera;
	D3DXMatrixLookAtLH(&camera, &m_eye, &m_target, &m_up);
	device->SetTransform(D3DTS_VIEW, &camera);

	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	m_rootViewObject->Update();
	m_rootViewObject->UpdateChile();

	device->Present(NULL, NULL, 0, NULL);
}

void ViewObjectMgr::SubscribeEvent() {
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, EventType_KeyDown);
	g_program->Get_m_wndProcEventMgr()->Subscribe(this, EventType_KeyUp);
}

void ViewObjectMgr::UnsubscribeEvent() {
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, EventType_KeyUp);
	g_program->Get_m_wndProcEventMgr()->Unsubscribe(this, EventType_KeyDown);
}

void ViewObjectMgr::MoveCameraToPosition(D3DXVECTOR3 const *position) {
	D3DXVECTOR3 moveVector = *position - m_eye;
	m_eye = *position;
	m_target = moveVector + m_target;
}

BOOL ViewObjectMgr::OnMessage(EventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case EventType_KeyDown:
	{
		switch (wParam) {
		case 'W':
		{
			return TRUE;
		}break;
		case 'S':
		{
			return TRUE;
		}break;
		case 'A':
		{
			return TRUE;
		}break;
		case 'D':
		{
			return TRUE;
		}break;
		}
	}break;
	case EventType_KeyUp:
	{
		switch (wParam) {
		case 'W':
		{
			return TRUE;
		}break;
		case 'S':
		{
			return TRUE;
		}break;
		case 'A':
		{
			return TRUE;
		}break;
		case 'D':
		{
			return TRUE;
		}break;
		}
	}break;
	}

	return FALSE;
}
