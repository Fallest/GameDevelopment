#ifndef FIRSTCPPGAME_PLAYER_H
#define FIRSTCPPGAME_PLAYER_H
#include "input.h"

namespace Player {
	struct Player {
		float x, y;
		float height, width;
		float speed;
	};

	extern Player PLAYER_ONE;
	extern Player PLAYER_TWO;

	extern void movePlayer(Player* player, Input::Input* input);
	extern void initializePlayers();
}

#endif