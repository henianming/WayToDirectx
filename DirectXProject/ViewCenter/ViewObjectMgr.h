#ifndef VIEW_OBJECT_MGR_H
#define VIEW_OBJECT_MGR_H

#include <list>
#include <d3dx9.h>
#include "EventCenter\WndProcEventMgr.h"

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
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual void OnGetFocus() = 0;
	virtual void OnLostFocus() = 0;
	virtual void Update();
};

class HViewObjectMgr {
private:
	HIViewObject *m_rootViewObject;
	
	float m_cameraSpeed;
	D3DXVECTOR3 m_eye;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_up;

public:
	BOOL Create();
	BOOL Release();
	void Update();
};

#endif //VIEW_OBJECT_MGR_H