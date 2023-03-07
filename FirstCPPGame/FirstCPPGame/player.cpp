#include "player.h"
#include "chrono.h"
#include "render.h"
#include "utils.h"

namespace Player {

	float playerHeight = 20.f, playerWidth = 5.f;
	float playerSpeed = 0.f;
	float acceleration = 6.f;
	float maxSpeed = 15.f;
	float friction = 2.f;

	// Make this MORE FUN (or annoying)
	bool BOUNCY = false;

	Player PLAYER_ONE, PLAYER_TWO;

	void movePlayer(Player* player, Input::Input* input) {
		float playerPos = player->y;
		float playerSpeed = player->speed;

		// Input control
		if (isDown(Input::BUTTON_UP, input)) {
			playerSpeed += (acceleration * Chrono::deltaTime);
		}
			
		if (isDown(Input::BUTTON_DOWN, input)) {
			playerSpeed -= (acceleration * Chrono::deltaTime);
		}

		// Variable updates
		playerSpeed = Utils::floatClamp(-maxSpeed, playerSpeed, maxSpeed);
		playerPos += playerSpeed;

		player->speed = playerSpeed;
		player->y = Utils::floatClamp(5.f, playerPos, 95.f - playerHeight);

		// Friction control
		if (player->speed > 0) {
			player->speed -= (friction * Chrono::deltaTime);
		}
		else if (player->speed < 0) {
			player->speed += (friction * Chrono::deltaTime);
		}

		// Boundaries control
		if (player->y == 5 || player->y == 95.f - playerHeight) {
			player->speed = BOUNCY ? -player->speed : 0;
		}
	}

	void initializePlayers() {
		PLAYER_ONE = {
			10,
			50.f - (playerHeight / 2.f),
			playerHeight,
			playerWidth,
			playerSpeed
			};
		PLAYER_TWO = {
			90 - Render::widthPercToHeightPerc(playerWidth),
			50.f - (playerHeight / 2.f),
			playerHeight,
			playerWidth,
			playerSpeed
		};
	}
}