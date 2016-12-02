#include "ViewObjectMgr.h"

#include "ViewObject/InitialViewObject.h"
#include "Common/CommonCode.h"
#include "program.h"

extern HProgram *g_program;

HIViewObject::~HIViewObject() {
	//clear child
	std::list<HIViewObject*>::iterator it = m_childViewObjectList.begin();
	while (it != m_childViewObjectList.end()) {
		delete (*it);

		it++;
	}

	//Hide();
	//Unload();
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

BOOL HViewObjectMgr::Create() {
	m_rootViewObject = new HInitialViewObject();
	m_rootViewObject->Load();
	m_rootViewObject->Show();

	return TRUE;
}

BOOL HViewObjectMgr::Release() {
	m_rootViewObject->Hide();
	m_rootViewObject->Unload();
	SAFEDELETENULL(m_rootViewObject);

	return TRUE;
}

void HViewObjectMgr::Update() {
	IDirect3DDevice9 *device = g_program->Get_m_device();
	D3DXMATRIX camera;
	D3DXMatrixLookAtLH(&camera, &m_eye, &m_target, &m_up);
	device->SetTransform(D3DTS_VIEW, &camera);

	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	m_rootViewObject->Update();
	m_rootViewObject->UpdateChile();

	device->Present(NULL, NULL, 0, NULL);
}