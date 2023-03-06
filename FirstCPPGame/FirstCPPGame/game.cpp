#include "game.h"
#include "input.h"
#include "render.h"
#include "utils.h"
#include "chrono.h"
#include "player.h"

namespace Game {

bool GAME_RUNNING = true;

Input::Input input = {};

void handlePlayerInput(int vkCode, bool isDown) {
	switch (vkCode) {
	case VK_UP: {
		input.buttons[Input::BUTTON_UP].hasChanged = isDown != input.buttons[Input::BUTTON_UP].isDown;
		input.buttons[Input::BUTTON_UP].isDown = isDown;
	} break;
	case VK_DOWN: {
		input.buttons[Input::BUTTON_DOWN].hasChanged = isDown != input.buttons[Input::BUTTON_DOWN].isDown;
		input.buttons[Input::BUTTON_DOWN].isDown = isDown;
	} break;
	case VK_RIGHT: {
		input.buttons[Input::BUTTON_RIGHT].hasChanged = isDown != input.buttons[Input::BUTTON_RIGHT].isDown;
		input.buttons[Input::BUTTON_RIGHT].isDown = isDown;
	} break;
	case VK_LEFT: {
		input.buttons[Input::BUTTON_LEFT].hasChanged = isDown != input.buttons[Input::BUTTON_LEFT].isDown;
		input.buttons[Input::BUTTON_LEFT].isDown = isDown;
	} break;
	}
}

void checkWndMsgs(MSG* message, HWND* window) {
	while (PeekMessage(message, *window, 0, 0, PM_REMOVE)) {

		switch (message->message) {
		case WM_KEYUP:
		case WM_KEYDOWN: {
			Utils::u32 vkCode = (Utils::u32)message->wParam;
			bool isDown = ((message->lParam & (1 << 31)) == 0);

			handlePlayerInput(vkCode, isDown);
		} break;

		default: {
			TranslateMessage(message);
			DispatchMessage(message);
		} break;
		}
	}
}

void simulateGame() {
	Render::clearScreen(0xff5500);
	if (isDown(Input::BUTTON_UP, &input)) Player::y += Player::speed * Chrono::deltaTime;
	if (isDown(Input::BUTTON_DOWN, &input)) Player::y -= Player::speed * Chrono::deltaTime;
	if (isDown(Input::BUTTON_RIGHT, &input)) Player::x += Player::speed * Chrono::deltaTime;
	if (isDown(Input::BUTTON_LEFT, &input)) Player::x -= Player::speed * Chrono::deltaTime;
	Render::drawHeightResponsiveRect(Player::x, Player::y, 10, 10, 0x00ff22);
	Render::drawHeightResponsiveRect(30, 30, 5, 5, 0x00ff22);
	Render::drawHeightResponsiveRect(25, 0, 8, 20, 0x00ff22);
}

void runGame(HWND* window) {
	// Game loop vars
	HDC hdc = GetDC(*window);

	Chrono::startChrono();
	
	// Game loop
	while (GAME_RUNNING) {
		// Input
		MSG message;

		// Reset the changed state of each button every frame
		for (int i = 0; i < Input::BUTTON_COUNT; i++) {
			input.buttons[i].hasChanged = false;
		}

		// This checks for window messages (docs: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea)
		checkWndMsgs(&message, window);

		// Simulate
		simulateGame();

		// Render
		StretchDIBits(
			hdc,
			0,
			0,
			Render::RENDER_STATE.WND_WIDTH,
			Render::RENDER_STATE.WND_HEIGHT,
			0,
			0,
			Render::RENDER_STATE.WND_WIDTH,
			Render::RENDER_STATE.WND_HEIGHT,
			Render::RENDER_STATE.WND_MEMORY,
			&Render::RENDER_STATE.WND_BITMAPINFO,
			DIB_RGB_COLORS,
			SRCCOPY
		);

		// Get last frame time and delta time
		Chrono::setDeltaTime();
	}
}
}