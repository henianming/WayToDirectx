#ifndef INPUT_EVENT_MGR_H
#define INPUT_EVENT_MGR_H

#include <Windows.h>
#include <list>
#include <vector>

enum HInputEventType {
//原始按键
//	键盘
	HInputEventType_RK_Min,
	//字母区，禁止插入_begin
	HInputEventType_RK_A,
	HInputEventType_RK_B,
	HInputEventType_RK_C,
	HInputEventType_RK_D,
	HInputEventType_RK_E,
	HInputEventType_RK_F,
	HInputEventType_RK_G,

	HInputEventType_RK_H,
	HInputEventType_RK_I,
	HInputEventType_RK_J,
	HInputEventType_RK_K,
	HInputEventType_RK_L,
	HInputEventType_RK_M,
	HInputEventType_RK_N,

	HInputEventType_RK_O,
	HInputEventType_RK_P,
	HInputEventType_RK_Q,
	HInputEventType_RK_R,
	HInputEventType_RK_S,
	HInputEventType_RK_T,

	HInputEventType_RK_U,
	HInputEventType_RK_V,
	HInputEventType_RK_W,
	HInputEventType_RK_X,
	HInputEventType_RK_Y,
	HInputEventType_RK_Z,
	//字母区，禁止插入_end
	HInputEventType_RK_Max,
//	手柄
	HInputEventType_RG_Min,
	HInputEventType_RG_Max,
//游戏识别按键
	HInputEventType_D_Min,
	HInputEventType_D_W,
	HInputEventType_D_A,
	HInputEventType_D_S,
	HInputEventType_D_D,
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