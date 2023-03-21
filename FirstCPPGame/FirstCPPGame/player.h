#ifndef FIRSTCPPGAME_PLAYER_H
#define FIRSTCPPGAME_PLAYER_H
#include "input.h"
#include "physics.h"
#include "chrono.h"

namespace Player {
	// Player class
	class Player : public Physics::Physics2Object {
	public:
		Player(
			Physics::Point2 position,
			Physics::Vector2 size,
			Physics::Vector2 speed,
			float friction
		) {
			this->friction = friction;
			this->position = position;
			this->size = size;
			this->speed = speed;
		}

		~Player() {}

		void move(Physics::Vector2 speed) {
			this->speed = speed;
			this->position = Physics::sumVectors({ {0, 0}, this->position }, speed).end;

			// Friction control
			Physics::Vector2 speedReduction = { {0, 0}, {0, this->friction * Chrono::deltaTime} }; // Only vertical
			Physics::Vector2 negativeSpeedReduction = { {0, 0}, {0, -this->friction * Chrono::deltaTime} }; // Only vertical
			if (Physics::distance(this->speed) < Physics::distance(speedReduction)) {
				this->speed = { {0, 0}, {0, 0} };
			}
			else if (Physics::distance(this->speed) > 0) {
				this->speed = Physics::sumVectors(this->speed, negativeSpeedReduction);
			}
			else if (Physics::distance(this->speed) < 0) {
				this->speed = Physics::sumVectors(this->speed, speedReduction);
			}
		}
	};

	extern Player PLAYER_ONE;
	extern Player PLAYER_TWO;

	extern void initializePlayers();
}

#endif