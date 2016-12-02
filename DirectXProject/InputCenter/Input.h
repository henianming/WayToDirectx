#if 0
#ifndef INPUT_H
#define INPUT_H

#include <Windows.h>

#include "EventCenter/WndProcEventMgr.h"
#include "EventCenter/InputEventMgr.h"

class HIInputDevice : public HIWndProcEventReceiver {
public:
	virtual BOOL Create() = 0;
	virtual BOOL Release() = 0;
	virtual BOOL Update() = 0;
};

#endif //INPUT_H
#endif