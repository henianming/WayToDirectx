#pragma once

#include <Windows.h>

//--------·Ö½çÏß-----------------------------------------------------------------
class HIInputDevice {
public:
	virtual BOOL Create() = 0;
	virtual BOOL Release() = 0;
	virtual BOOL Update() = 0;
};