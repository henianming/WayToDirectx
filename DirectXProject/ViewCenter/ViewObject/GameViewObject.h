#pragma once

#include "../ViewObjectMgr.h"
#include "EventCenter/WndProcEventMgr.h"

//--------�ֽ���-----------------------------------------------------------------
class HIGameViewItem {
public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void Update();
};

//--------�ֽ���-----------------------------------------------------------------
class HGameViewObject : public HIViewObject, public HIWndProcEventReceiver {
private:
	IDirect3DDevice9 *m_device;

	HIGameViewItem *m_coordinateAxix;

public:
	virtual void Load();
	virtual void Unload();
	virtual void Show();
	virtual void Hide();
	virtual void OnGetFocus();
	virtual void OnLostFocus();
	virtual void Update();

public:
	virtual BOOL OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam);
};