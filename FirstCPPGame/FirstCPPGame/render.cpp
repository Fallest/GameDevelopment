#include "render.h"

namespace Render {
	float RENDER_SCALE = 0.01f;
	RenderState RENDER_STATE;

	void clearScreen(Utils::u32 color) {
		Utils::u32* pixel = (Utils::u32*)RENDER_STATE.WND_MEMORY;
		for (int y = 0; y < RENDER_STATE.WND_HEIGHT; y++) {
			for (int x = 0; x < RENDER_STATE.WND_WIDTH; x++) {
				*pixel++ = color;
			}
		}
	}

	void
		drawRectInPixels(Physics::Vector2 rect, Utils::u32 color) {
		rect = Physics::clampVector2(
			{ {0, 0}, {(float)RENDER_STATE.WND_WIDTH, (float)RENDER_STATE.WND_HEIGHT} },
			rect
		);

		for (int y = rect.start.y; y < rect.end.y; y++) {
			Utils::u32* pixel = 
				(Utils::u32*)RENDER_STATE.WND_MEMORY + 
				(int)rect.start.x +
				y * 
				RENDER_STATE.WND_WIDTH;

			for (int x = rect.start.x; x < rect.end.x; x++) {
				*pixel++ = color;
			}
		}
	}

	/**
	 * Receives the lower-left corner coordinates(%), and draws a rectangle given its height(%), width(%), and color.
	 * The position is absolute (responsive on both height and width).
	 * The size of the rect is responsive on height.
	 */
	void
		drawHeightResponsiveRect(Physics::Vector2 rect, Utils::u32 color) {
		// Change to pixels
		rect.start.x *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		rect.start.y *= (RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect.end.x *= ((float)RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect.end.y *= (RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect.end = Physics::sumPoints(rect.end, rect.start);

		drawRectInPixels(rect, color);
	}

	/**
	 * Receives the lower-left corner coordinates(%), and draws a rectangle given its height(%), width(%), and color.
	 * The position is absolute (responsive on both height and width).
	 * The size of the rect is responsive on width.
	 */
	void
		drawWidthResponsiveRect(Physics::Vector2 rect, Utils::u32 color) {
		// Change to pixels
		rect.start.x *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		rect.start.y *= (RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect.end.x *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		rect.end.y *= (RENDER_STATE.WND_WIDTH) * RENDER_SCALE;

		drawRectInPixels(rect, color);
	}

	/**
	 * Receives the lower-left corner coordinates(%), and draws a rectangle given its height(%), width(%), and color.
	 * The position is absolute (responsive on both height and width).
	 * The size of the rect is responsive on height and width.
	 */
	void drawResponsiveRect(Physics::Vector2 rect, Utils::u32 color) {
		// Change to pixels
		rect.start.x *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		rect.start.y *= (RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect.end.x *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		rect.end.y *= (RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;

		drawRectInPixels(rect, color);
	}

	float widthPercToHeightPerc(float widthPerc) {
		return (widthPerc * RENDER_STATE.WND_HEIGHT) / (RENDER_STATE.WND_WIDTH);
	}

	float heightPercToWidthPerc(float heightPerc) {
		return (heightPerc * RENDER_STATE.WND_HEIGHT) / (RENDER_STATE.WND_WIDTH);
	}
}