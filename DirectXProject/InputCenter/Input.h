#pragma once

#include <Windows.h>

//--------�ֽ���-----------------------------------------------------------------
class HIInputDevice {
public:
	virtual BOOL Create() = 0;
	virtual BOOL Release() = 0;
	virtual BOOL Update() = 0;
};