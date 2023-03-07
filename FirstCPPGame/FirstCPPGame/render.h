#ifndef FIRSTCPPGAME_RENDER_H
#define FIRSTCPPGAME_RENDER_H
#include "utils.h"
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

extern void drawRectInPixels(int x0, int y0, int x1, int y1, Utils::u32 color);

extern void drawHeightResponsiveRect(
	float x, 
	float y,
	float rect_width, 
	float rect_height, 
	Utils::u32 color
);

extern void drawWidthResponsiveRect(
	float x,
	float y,
	float rect_width,
	float rect_height,
	Utils::u32 color
);

extern void drawResponsiveRect(
	float x,
	float y,
	float rect_width,
	float rect_height,
	Utils::u32 color
);

extern float widthPercToHeightPerc(float widthPerc);
extern float heightPercToWidthPerc(float heightPerc);

}
#endif