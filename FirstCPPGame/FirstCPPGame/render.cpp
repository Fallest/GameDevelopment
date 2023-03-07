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
		drawRectInPixels(int x0, int y0, int x1, int y1, Utils::u32 color) {
		x0 = Utils::clamp(0, x0, RENDER_STATE.WND_WIDTH);
		x1 = Utils::clamp(0, x1, RENDER_STATE.WND_WIDTH);
		y0 = Utils::clamp(0, y0, RENDER_STATE.WND_HEIGHT);
		y1 = Utils::clamp(0, y1, RENDER_STATE.WND_HEIGHT);

		for (int y = y0; y < y1; y++) {
			Utils::u32* pixel = (Utils::u32*)RENDER_STATE.WND_MEMORY + x0 + y * RENDER_STATE.WND_WIDTH;
			for (int x = x0; x < x1; x++) {
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
		drawHeightResponsiveRect(float x, float y, float rect_width, float rect_height, Utils::u32 color) {
		// Change to pixels
		x *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		y *= ((float)RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect_width *= ((float)RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect_height *= ((float)RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;

		int x1 = x + rect_width;
		int y1 = y + rect_height;

		drawRectInPixels(x, y, x1, y1, color);
	}

	/**
	 * Receives the lower-left corner coordinates(%), and draws a rectangle given its height(%), width(%), and color.
	 * The position is absolute (responsive on both height and width).
	 * The size of the rect is responsive on width.
	 */
	void
		drawWidthResponsiveRect(float x, float y, float rect_width, float rect_height, Utils::u32 color) {
		// Change to pixels
		x *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		y *= ((float)RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect_width *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		rect_height *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;

		int x1 = x + rect_width;
		int y1 = y + rect_height;

		drawRectInPixels(x, y, x1, y1, color);
	}

	/**
	 * Receives the lower-left corner coordinates(%), and draws a rectangle given its height(%), width(%), and color.
	 * The position is absolute (responsive on both height and width).
	 * The size of the rect is responsive on height and width.
	 */
	void
		drawResponsiveRect(float x, float y, float rect_width, float rect_height, Utils::u32 color) {
		// Change to pixels
		x *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		y *= ((float)RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;
		rect_width *= ((float)RENDER_STATE.WND_WIDTH) * RENDER_SCALE;
		rect_height *= ((float)RENDER_STATE.WND_HEIGHT) * RENDER_SCALE;

		int x1 = x + rect_width;
		int y1 = y + rect_height;

		drawRectInPixels(x, y, x1, y1, color);
	}

	float widthPercToHeightPerc(float widthPerc) {
		return (widthPerc * RENDER_STATE.WND_HEIGHT) / (RENDER_STATE.WND_WIDTH);
	}

	float heightPercToWidthPerc(float heightPerc) {
		return (heightPerc * RENDER_STATE.WND_HEIGHT) / (RENDER_STATE.WND_WIDTH);
	}
}