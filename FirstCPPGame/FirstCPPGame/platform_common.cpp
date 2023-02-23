struct Button_State {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_COUNT, // Should be the last item
};

struct Input {
	Button_State buttons[BUTTON_COUNT];
};

#define process_button(b, vk)\
case vk: {\
	input.buttons[b].is_down = is_down;\
	input.buttons[b].changed = true;\
} break;