#include "InitialViewObject.h"

void InitialViewObject::Load() {
	AddChildViewObject(&m_coordinateAxis);
	m_coordinateAxis.Load();
}

void InitialViewObject::Unload() {
	m_coordinateAxis.Unload();
	DelChildViewObject(&m_coordinateAxis);
}

void InitialViewObject::Show() {

}

void InitialViewObject::Hide() {

}

void InitialViewObject::Update() {

}
