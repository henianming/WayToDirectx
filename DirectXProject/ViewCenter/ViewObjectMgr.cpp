#include "ViewObjectMgr.h"

#include "ViewObject/InitialViewObject.h"
#include "Common/CommonCode.h"

void IViewObject::SetParentViewObject(IViewObject *parent, BOOL isOtherCall) {
	if (m_parentViewObject != NULL) {
		UnsetParentViewObject();
	}

	m_parentViewObject = parent;
	if (isOtherCall == TRUE) {
		m_parentViewObject->AddChildViewObject(this, FALSE);
	}
}

void IViewObject::UnsetParentViewObject(BOOL isOtherCall) {
	if (m_parentViewObject == NULL) {
		return;
	}

	if (isOtherCall == TRUE) {
		m_parentViewObject->DelChildViewObject(this, FALSE);
	}
	m_parentViewObject = NULL;
}

void IViewObject::AddChildViewObject(IViewObject *child, BOOL isOtherCall) {
	if (child == NULL) {
		return;
	}

	m_childViewObjectList.push_back(child);
	if (isOtherCall == TRUE) {
		child->SetParentViewObject(this, FALSE);
	}
}

void IViewObject::DelChildViewObject(IViewObject *child, BOOL isOtherCall) {
	std::list<IViewObject*>::iterator it = m_childViewObjectList.begin();
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

void IViewObject::UpdateChile() {
	std::list<IViewObject*>::iterator it = m_childViewObjectList.begin();
	while (it != m_childViewObjectList.end()) {
		(*it)->Update();
		(*it)->UpdateChile();
		it++;
	}
}

void IViewObject::Update() {

}

BOOL ViewObjectMgr::Create() {
	m_rootViewObject = new InitialViewObject();
	m_rootViewObject->Load();
	m_rootViewObject->Show();
}

BOOL ViewObjectMgr::Release() {
	m_rootViewObject->Hide();
	m_rootViewObject->Show();
	SAFEDELETENULL(m_rootViewObject);
}

void ViewObjectMgr::Update() {
	m_rootViewObject->Update();
	m_rootViewObject->UpdateChile();
}
