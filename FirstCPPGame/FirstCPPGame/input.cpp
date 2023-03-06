#include "input.h"

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


}