#ifndef FIRSTCPPGAME_RENDER_H
#define FIRSTCPPGAME_RENDER_H
#include "utils.h"
#include "physics.h"
#include <Windows.h>

namespace Render {

struct RenderState {
	int WND_HEIGHT, WND_WIDTH;
	float WND_ASPECT_RATIO;
	void* WND_MEMORY;

	BITMAPINFO WND_BITMAPINFO;
};

extern RenderState RENDER_STATE;

extern float RENDER_SCALE;

extern void clearScreen(Utils::u32 color);

extern void drawRectInPixels(
	Physics::Vector2 rect, 
	Utils::u32 color
);

extern void drawHeightResponsiveRect(
	Physics::Vector2 rect, 
	Utils::u32 color
);

extern void drawWidthResponsiveRect(
	Physics::Vector2 rect,
	Utils::u32 color
);

extern void drawResponsiveRect(
	Physics::Vector2 rect,
	Utils::u32 color
);

extern float widthPercToHeightPerc(float widthPerc);
extern float heightPercToWidthPerc(float heightPerc);

}
#endif