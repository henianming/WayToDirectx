#ifndef INITIAL_VIEW_OBJECT_H
#define INITIAL_VIEW_OBJECT_H

#include "../ViewObjectMgr.h"

class HGameViewObject : public HIViewObject {
public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void OnGetFocus();
	virtual void OnLostFocus();
	virtual void Update();
};

#endif //INITIAL_VIEW_OBJECT_H