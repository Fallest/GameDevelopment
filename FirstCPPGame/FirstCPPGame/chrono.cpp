#include "chrono.h"

namespace Chrono {

	float deltaTime = 0.016666f;

	void startChrono() {
		QueryPerformanceCounter(&frameBeginTime);
		QueryPerformanceFrequency(&performanceQuery);
		performanceFrequency = (float)performanceQuery.QuadPart;
	}

	void setDeltaTime() {
		QueryPerformanceCounter(&frameEndTime);
		deltaTime = (float)(frameEndTime.QuadPart - frameBeginTime.QuadPart) / performanceFrequency;
		frameBeginTime = frameEndTime;
	}

}