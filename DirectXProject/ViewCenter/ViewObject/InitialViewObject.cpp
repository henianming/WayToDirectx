#include "InitialViewObject.h"

#include "CoordinateAxis.h"

void InitialViewObject::Load() {
	AddChildViewObject(&m_coordinateAxis);
}

void InitialViewObject::Unload() {
	DelChildViewObject(&m_coordinateAxis);
}

void InitialViewObject::Show() {

}

void InitialViewObject::Hide() {

}

void InitialViewObject::Update() {

}
