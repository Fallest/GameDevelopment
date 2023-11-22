#include "player.h"
#include "chrono.h"
#include "render.h"
#include "utils.h"
#include "game.h"
#include <cmath>

namespace Player {

	// TODO Move most of this to the 
	float acceleration = 6.f;
	float maxSpeed = 15;

	Player* PLAYER_ONE;
	Player* PLAYER_TWO;

	void movePlayer(Player* player, Input::Input* input) {
		Physics::Point2 playerPos = player->position;
		Physics::Vector2 playerSpeed = player->speed;

		// Input control
		if (isDown(Input::BUTTON_UP, input)) {
			playerSpeed = Physics::sumVectors(
				playerSpeed, 
				{ {0, 0}, {0, (acceleration * Chrono::deltaTime)} } // ONLY VERTICAL
			);
		}
			
		if (isDown(Input::BUTTON_DOWN, input)) {
			playerSpeed = Physics::sumVectors(
				playerSpeed,
				{ {0, 0}, {0, -(acceleration * Chrono::deltaTime)} } // ONLY VERTICAL
			);
		}

		playerSpeed = Physics::clampVector2({ {0, -maxSpeed}, {0, maxSpeed} }, playerSpeed);
		playerPos = Physics::clampPoint2({ {Game::ARENA.start}, {Game::ARENA.end.x - player->size.end.x, Game::ARENA.end.y - player->size.end.y} }, playerPos);
		
		// Control the border
		if (player->position.y < 5.f || player->position.y > 95.f - player->size.end.y) {
			playerSpeed = { {0, 0}, {0, 0} };
		}

		// Move the player and limit its position
		player->position = playerPos;
		player->move(playerSpeed);
	}

	// TODO Update the player initialization with the new physics update
	void initializePlayers() {
		float friction = 2.f;
		float playerHeight = 20, playerWidth = 5;
		float playerSpeed = 0;

		PLAYER_ONE = new Player(
			{ 10.f, (50.f - (playerHeight / 2.f)) },
			{ {0.f, 0.f}, {playerWidth, playerHeight} },
			{ {0.f, 0.f}, {0.f, playerSpeed} },
			2.f); 
		PLAYER_TWO = new Player(
			{ 90 - Render::widthPercToHeightPerc(playerWidth), (50.f - (playerHeight / 2.f)) },
			{ {0, 0}, {playerWidth, playerHeight} },
			{ {0, 0}, {0, playerSpeed} },
			2.f);
	}
}