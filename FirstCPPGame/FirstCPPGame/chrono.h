#ifndef FIRSTCPPGAME_CHRONO_H
#define FIRSTCPPGAME_CHRONO_H
#include <Windows.h>

namespace Chrono {

extern float deltaTime;
static float performanceFrequency;
static LARGE_INTEGER frameBeginTime, frameEndTime, performanceQuery;

extern void startChrono();

extern void setDeltaTime();

}

#endif