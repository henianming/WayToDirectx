#ifndef INITIAL_VIEW_OBJECT_H
#define INITIAL_VIEW_OBJECT_H

#include "../ViewObjectMgr.h"
#include "CoordinateAxis.h"

class HInitialViewObject/* : public HIViewObject */{
	HCoordinateAxis m_coordinateAxis;

public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void Update();
};

#endif //INITIAL_VIEW_OBJECT_H