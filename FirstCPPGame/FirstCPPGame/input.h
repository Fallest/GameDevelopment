#ifndef FIRSTCPPGAME_INPUT_H
#define FIRSTCPPGAME_INPUT_H

namespace Input {

struct ButtonState {
	bool isDown;
	bool hasChanged;
};

enum ButtonsEnum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT, // Should be the last item
};

struct Input {
	ButtonState buttons[BUTTON_COUNT];
};

extern bool isDown(int b, Input* input);
extern bool isPressed(int b, Input* input);
extern bool isReleased(int b, Input* input);

}

#endif