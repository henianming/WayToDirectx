#pragma once

#include <list>
#include <d3dx9.h>
#include "EventCenter\WndProcEventMgr.h"

//--------分界线-----------------------------------------------------------------
class HIViewObject {
private:
	HIViewObject *m_parentViewObject;
	std::list<HIViewObject*> m_childViewObjectList;

public:
	~HIViewObject();

	VOID SetParentViewObject(HIViewObject *parent, BOOL isOtherCall = TRUE);
	VOID UnsetParentViewObject(BOOL isOtherCall = TRUE);
	VOID AddChildViewObject(HIViewObject *child, BOOL isOtherCall = TRUE);
	VOID DelChildViewObject(HIViewObject *child, BOOL isOtherCall = TRUE);
	VOID UpdateChile();

public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID OnGetFocus();
	virtual VOID OnLostFocus();
	virtual VOID Update();
};

//--------分界线-----------------------------------------------------------------
class HViewObjectMgr {
private:
	HIViewObject *m_gameViewObject;
	HIViewObject *m_uiViewObject;

public:
	BOOL Create();
	BOOL Release();
	VOID Update();
};