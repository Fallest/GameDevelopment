#ifndef FIRSTCPPGAME_GAME_H
#define FIRSTCPPGAME_GAME_H
#include <Windows.h>

namespace Game {

	extern bool GAME_RUNNING;

	void checkWndMsgs(MSG* message, HWND* window);

	void simulateGame();

	extern void runGame(HWND* window);
}

#endif