#include "InitialViewObject.h"

void HInitialViewObject::Load() {
//	AddChildViewObject(&m_coordinateAxis);
	m_coordinateAxis.Load();
}

void HInitialViewObject::Unload() {
	m_coordinateAxis.Unload();
	//DelChildViewObject(&m_coordinateAxis);
}

void HInitialViewObject::Show() {

}

void HInitialViewObject::Hide() {

}

void HInitialViewObject::Update() {

}
