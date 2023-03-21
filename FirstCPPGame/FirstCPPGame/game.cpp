#include "game.h"
#include "input.h"
#include "render.h"
#include "utils.h"
#include "chrono.h"
#include "player.h"

namespace Game {
	
static Physics::Vector2 ARENA = { {0, 5}, {5, 95} };

bool GAME_RUNNING = true;

Input::Input inputPlayerOne = {}, inputPlayerTwo = {};

void checkWndMsgs(MSG* message, HWND* window) {
	while (PeekMessage(message, *window, 0, 0, PM_REMOVE)) {

		switch (message->message) {
		case WM_KEYUP:
		case WM_KEYDOWN: {
			Utils::u32 vkCode = (Utils::u32)message->wParam;
			bool isDown = ((message->lParam & (1 << 31)) == 0);

			if (vkCode > 0x40) {
				Input::handleInput(vkCode, isDown, &inputPlayerOne);
			}
			else {
				Input::handleInput(vkCode, isDown, &inputPlayerTwo);
			}
		} break;

		default: {
			TranslateMessage(message);
			DispatchMessage(message);
		} break;
		}
	}
}

// TODO Update all Player and Render references
void simulateGame() {
	Render::clearScreen(Utils::PALETTE.complementary.darker); // BORDER
	Render::drawResponsiveRect(
		ARENA,
		Utils::PALETTE.complementary.foggy
	);  // ARENA

	Player::movePlayer(&Player::PLAYER_ONE, &inputPlayerOne);
	Player::movePlayer(&Player::PLAYER_TWO, &inputPlayerTwo);

	Render::drawHeightResponsiveRect(
		Player::PLAYER_ONE.x,
		Player::PLAYER_ONE.y,
		Player::PLAYER_ONE.width,
		Player::PLAYER_ONE.height,
		Utils::PALETTE.secondary.main
	);  // PLAYER_ONE

	Render::drawHeightResponsiveRect(
		Player::PLAYER_TWO.x,
		Player::PLAYER_TWO.y,
		Player::PLAYER_TWO.width,
		Player::PLAYER_TWO.height,
		Utils::PALETTE.primary.main
	);  // PLAYER_TWO
}

void runGame(HWND* window) {
	// Game loop vars
	HDC hdc = GetDC(*window);

	Chrono::startChrono();
	Player::initializePlayers();
	
	// Game loop
	while (GAME_RUNNING) {
		// Input
		MSG message;

		// Reset the changed state of each button every frame
		for (int i = 0; i < Input::BUTTON_COUNT; i++) {
			inputPlayerOne.buttons[i].hasChanged = false;
			inputPlayerTwo.buttons[i].hasChanged = false;
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