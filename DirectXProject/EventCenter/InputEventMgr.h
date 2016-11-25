#ifndef INPUT_EVENT_MGR_H
#define INPUT_EVENT_MGR_H

#include <Windows.h>
#include <list>
#include <vector>

enum HInputEventType {
	HInputEventType_Min = 0,
//原始按键
//	键盘
//	手柄
//游戏识别按键
	HInputEventType_Max,
};

class HIInputEventReceiver {
public:
	virtual BOOL OnMessage(HInputEventType eventType, double durationTime, BOOL isContinue) = 0;
};

class HInputEventMgr {
private:
	typedef std::list<HIInputEventReceiver*> M_RL;
	typedef std::vector<M_RL*> M_ETV;

private:
	M_ETV m_etv;

public:
	BOOL Create();
	BOOL Release();

	void Subscribe(HIInputEventReceiver *receiver, HInputEventType eventType);
	void Unsubscribe(HIInputEventReceiver *receiver, HInputEventType eventType);
	BOOL FireEvent(HInputEventType eventType, double durationTime, BOOL isContinue);
};

#endif //INPUT_EVENT_MGR_H