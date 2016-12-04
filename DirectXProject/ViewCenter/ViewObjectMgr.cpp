#include "ViewObjectMgr.h"

#include "ViewObject/GameViewObject.h"
#include "Common/CommonCode.h"
#include "program.h"

extern HProgram *g_program;

//--------分界线-----------------------------------------------------------------
HIViewObject::~HIViewObject() {
	//clear child
	std::list<HIViewObject*>::reverse_iterator rit = m_childViewObjectList.rbegin();
	while (rit != m_childViewObjectList.rend()) {
		delete (*rit);

		rit++;
	}

	Hide();
	Unload();
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

void HIViewObject::Load() {

}

void HIViewObject::Unload() {

}

void HIViewObject::Show() {

}

void HIViewObject::Hide() {

}

void HIViewObject::OnGetFocus() {

}

void HIViewObject::OnLostFocus() {

}

void HIViewObject::Update() {

}

//--------分界线-----------------------------------------------------------------
BOOL HViewObjectMgr::Create() {
	m_gameViewObject = new HGameViewObject();
	m_gameViewObject->Load();
	m_gameViewObject->Show();
	m_gameViewObject->OnGetFocus();

	return TRUE;
}

BOOL HViewObjectMgr::Release() {
	m_gameViewObject->OnLostFocus();
	m_gameViewObject->Hide();
	m_gameViewObject->Unload();
	SAFEDELETENULL(m_gameViewObject);

	return TRUE;
}

void HViewObjectMgr::Update() {
	HRESULT hr;

	IDirect3DDevice9 *device = g_program->Get_m_device();

	hr = device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	m_gameViewObject->Update();
	m_gameViewObject->UpdateChile();

	hr = device->Present(NULL, NULL, 0, NULL);
}