#ifndef VIEW_OBJECT_MGR_H
#define VIEW_OBJECT_MGR_H

#include <Windows.h>
#include <list>

class IViewObject {
private:
	IViewObject *m_parentViewObject;
	std::list<IViewObject*> m_childViewObjectList;

public:
	void SetParentViewObject(IViewObject *parent, BOOL isOtherCall = TRUE);
	void UnsetParentViewObject(BOOL isOtherCall = TRUE);
	void AddChildViewObject(IViewObject *child, BOOL isOtherCall = TRUE);
	void DelChildViewObject(IViewObject *child, BOOL isOtherCall = TRUE);
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
	IViewObject *m_rootViewObject;

public:
	BOOL Create();
	BOOL Release();
	void Update();
};

#endif //VIEW_OBJECT_MGR_H