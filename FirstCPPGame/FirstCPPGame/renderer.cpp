internal void
clear_screen(u32 color) {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

/**
 * Receives the lower-left corner coordinates (as a percentage), and draws a rectangle given its height(%), width(%), and color.
 * The size of the rect is responsive on width, not on height.
 */
internal void
draw_rect(float x, float y, float rect_width, float rect_height, u32 color) {
	// Change to pixels
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	rect_width *= render_state.height * render_scale;
	rect_height *= render_state.height * render_scale;

	int x1 = x + rect_width;
	int y1 = y + rect_height;

	draw_rect_in_pixels(x, y, x1, y1, color);
}