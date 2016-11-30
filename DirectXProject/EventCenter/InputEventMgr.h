#ifndef INPUT_EVENT_MGR_H
#define INPUT_EVENT_MGR_H

#include <Windows.h>
#include <list>
#include <vector>

enum HInputEventType {
//ԭʼ����
//	����
	HInputEventType_RK_Min,
	HInputEventType_RK_Max,
//	�ֱ�
	HInputEventType_RG_Min,
	HInputEventType_RG_Max,
//��Ϸʶ�𰴼�
	HInputEventType_D_Min,
	HInputEventType_D_Max,
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