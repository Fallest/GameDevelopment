#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player_x, player_y = 0.f;
float player_speed = 50.f;

internal void
simulate_game(Input* input, float dt) {
	clear_screen(0xff5500);
	if (is_down(BUTTON_UP)) player_y += player_speed*dt;
	if (is_down(BUTTON_DOWN)) player_y -= player_speed*dt;
	if (is_down(BUTTON_RIGHT)) player_x += player_speed*dt;
	if (is_down(BUTTON_LEFT)) player_x -= player_speed*dt;
	draw_rect(player_x, player_y, 10, 10, 0x00ff22);
	draw_rect(30, 30, 5, 5, 0x00ff22);
	draw_rect(25, 0, 8, 20, 0x00ff22);
}

internal void
run_game(HWND window) {
	// Game loop vars
	HDC hdc = GetDC(window);
	Input input = {};

	// To store time between frames
	float delta_time = 0.016666f;

	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);
	// 
	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}

	// Game loop
	while (running) {
		// Input
		MSG message;

		// Reset the changed state of each button every frame
		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		// This checks for window messages (docs: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-peekmessagea)
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

				switch (vk_code) {
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					process_button(BUTTON_LEFT, VK_LEFT);
				}

			} break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			} break;
			}
		}

		// Simulate
		simulate_game(&input, delta_time);

		// render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}
}