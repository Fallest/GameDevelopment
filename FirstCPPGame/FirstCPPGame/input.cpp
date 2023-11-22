#include "input.h"
#include <Windows.h>

namespace Input {

bool isDown(int b, Input* input) {
	return input->buttons[b].isDown;
}

bool isPressed(int b, Input* input) {
	return (input->buttons[b].isDown && input->buttons[b].hasChanged);
}

bool isReleased(int b, Input* input) {
	return (!input->buttons[b].isDown && input->buttons[b].hasChanged);
}

void changeInputValue(Input* input, bool isDown, ButtonsEnum button) {
	input->buttons[button].hasChanged = isDown != input->buttons[button].isDown;
	input->buttons[button].isDown = isDown;
}

void handleInput(int vkCode, bool isDown, Input* input) {
	switch (vkCode) {
	case VK_UP: 
	case 0x57: {
		changeInputValue(input, isDown, BUTTON_UP);
	} break;
	case VK_DOWN:
	case 0x53: {
		changeInputValue(input, isDown, BUTTON_DOWN);
	} break;
	case VK_RIGHT:
	case 0x44: {
		changeInputValue(input, isDown, BUTTON_RIGHT);
	} break;
	case VK_LEFT:
	case 0x41: {
		changeInputValue(input, isDown, BUTTON_LEFT);
	} break;
	}
}

}