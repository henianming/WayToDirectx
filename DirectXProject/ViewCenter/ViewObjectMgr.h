#pragma once

#include <list>
#include <d3dx9.h>
#include "EventCenter\WndProcEventMgr.h"

//--------�ֽ���-----------------------------------------------------------------
class HIViewObject {
private:
	HIViewObject *m_parentViewObject;
	std::list<HIViewObject*> m_childViewObjectList;

public:
	~HIViewObject();

	void SetParentViewObject(HIViewObject *parent, BOOL isOtherCall = TRUE);
	void UnsetParentViewObject(BOOL isOtherCall = TRUE);
	void AddChildViewObject(HIViewObject *child, BOOL isOtherCall = TRUE);
	void DelChildViewObject(HIViewObject *child, BOOL isOtherCall = TRUE);
	void UpdateChile();

public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void OnGetFocus();
	virtual void OnLostFocus();
	virtual void Update();
};

//--------�ֽ���-----------------------------------------------------------------
class HViewObjectMgr {
private:
	HIViewObject *m_gameViewObject;
	HIViewObject *m_uiViewObject;

public:
	BOOL Create();
	BOOL Release();
	void Update();
};