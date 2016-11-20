#ifndef VIEW_OBJECT_MGR_H
#define VIEW_OBJECT_MGR_H

#include <list>
#include <d3dx9.h>

class HIViewObject {
private:
	HIViewObject *m_parentViewObject;
	std::list<HIViewObject*> m_childViewObjectList;

public:
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
	virtual void Update();
};

class ViewObjectMgr {
private:
	HIViewObject *m_rootViewObject;

	D3DXVECTOR3 m_eye;
	D3DXVECTOR3 m_target;
	D3DXVECTOR3 m_up;

public:
	BOOL Create();
	BOOL Release();
	void Update();
};

#endif //VIEW_OBJECT_MGR_H