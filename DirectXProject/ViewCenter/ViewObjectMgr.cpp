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

VOID HIViewObject::SetParentViewObject(HIViewObject *parent, BOOL isOtherCall) {
	if (m_parentViewObject != NULL) {
		UnsetParentViewObject();
	}

	m_parentViewObject = parent;
	if (isOtherCall == TRUE) {
		m_parentViewObject->AddChildViewObject(this, FALSE);
	}
}

VOID HIViewObject::UnsetParentViewObject(BOOL isOtherCall) {
	if (m_parentViewObject == NULL) {
		return;
	}

	if (isOtherCall == TRUE) {
		m_parentViewObject->DelChildViewObject(this, FALSE);
	}
	m_parentViewObject = NULL;
}

VOID HIViewObject::AddChildViewObject(HIViewObject *child, BOOL isOtherCall) {
	if (child == NULL) {
		return;
	}

	m_childViewObjectList.push_back(child);
	if (isOtherCall == TRUE) {
		child->SetParentViewObject(this, FALSE);
	}
}

VOID HIViewObject::DelChildViewObject(HIViewObject *child, BOOL isOtherCall) {
	std::list<HIViewObject*>::iterator it = m_childViewObjectList.begin();
	while (it != m_childViewObjectList.end()) {
		if ((INT)(*it) == (INT)child) {
			if (isOtherCall == TRUE) {
				(*it)->UnsetParentViewObject(FALSE);
			}
			m_childViewObjectList.erase(it);
			return;
		}

		it++;
	}
}

VOID HIViewObject::UpdateChile() {
	std::list<HIViewObject*>::iterator it = m_childViewObjectList.begin();
	while (it != m_childViewObjectList.end()) {
		(*it)->Update();
		(*it)->UpdateChile();
		it++;
	}
}

VOID HIViewObject::Load() {

}

VOID HIViewObject::Unload() {

}

VOID HIViewObject::Show() {

}

VOID HIViewObject::Hide() {

}

VOID HIViewObject::OnGetFocus() {

}

VOID HIViewObject::OnLostFocus() {

}

VOID HIViewObject::Update() {

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

VOID HViewObjectMgr::Update() {
	HRESULT hr;

	IDirect3DDevice9 *device = g_program->Get_m_device();

	hr = device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	m_gameViewObject->Update();
	m_gameViewObject->UpdateChile();

	hr = device->Present(NULL, NULL, 0, NULL);
}