#include "Input.h"
#include "KeyboardInput.h"

HIInputDevice* HInputDeviceFactory::GetInputDevice(HInputDeviceType deviceType) {
	switch (deviceType) {
	case HInputDeviceType_Keyboard:
	{
		return new HKeyboardInput();
	}break;
	}

	return NULL;
}
