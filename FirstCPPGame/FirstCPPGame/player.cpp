#include "player.h"
#include "chrono.h"
#include "render.h"
#include "utils.h"
#include <cmath>

namespace Player {

	// TODO Move most of this to the initialization
	float playerHeight = 20.f, playerWidth = 5.f;
	float playerSpeed = 0.f;
	float acceleration = 6.f;
	int maxSpeed = 15;
	float friction = 2.f;

	Player PLAYER_ONE, PLAYER_TWO;

	void movePlayer(Player* player, Input::Input* input) {
		Physics::Point2 playerPos = player->position;
		Physics::Vector2 playerSpeed = player->speed;

		// Input control
		if (isDown(Input::BUTTON_UP, input)) {
			playerSpeed = Physics::sumVectors(
				playerSpeed, 
				{ {0, 0}, {0, (int)(acceleration * Chrono::deltaTime)} } // ONLY VERTICAL
			);
		}
			
		if (isDown(Input::BUTTON_DOWN, input)) {
			playerSpeed = Physics::sumVectors(
				playerSpeed,
				{ {0, 0}, {0, -(int)(acceleration * Chrono::deltaTime)} } // ONLY VERTICAL
			);
				
		}

		// Limit the speed
		playerSpeed = Physics::clampVector2({ {0, -maxSpeed}, {0, maxSpeed} }, playerSpeed);

		// Control the border
		if (player->position.y == 5 || player->position.y == 95.f - player->size.end.y) {
			playerSpeed = { {0, 0}, {0, 0} };
		}

		// Move the player
		player->move(playerSpeed);		
	}

	// TODO Update the player initialization with the new physics update
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