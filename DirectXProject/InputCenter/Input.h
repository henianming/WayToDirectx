#pragma once

#include <Windows.h>

enum HInputDeviceType {
	HInputDeviceType_Keyboard,
	HInputDeviceType_Gamepad,
};

//--------�ֽ���-----------------------------------------------------------------
class HIInputDevice {
public:
	virtual BOOL Create() = 0;
	virtual BOOL Release() = 0;
	virtual BOOL Update() = 0;
};

//--------�ֽ���-----------------------------------------------------------------
class HInputDeviceFactory {
private:
	HInputDeviceFactory();

public:
	static HIInputDevice* GetInputDevice(HInputDeviceType deviceType);
};