#pragma once

#include <Windows.h>

enum HInputDeviceType {
	HInputDeviceType_Keyboard,
	HInputDeviceType_Gamepad,
};

//--------分界线-----------------------------------------------------------------
class HIInputDevice {
public:
	virtual BOOL Create() = 0;
	virtual BOOL Release() = 0;
	virtual BOOL Update() = 0;
};

//--------分界线-----------------------------------------------------------------
class HInputDeviceFactory {
private:
	HInputDeviceFactory();

public:
	static HIInputDevice* GetInputDevice(HInputDeviceType deviceType);
};