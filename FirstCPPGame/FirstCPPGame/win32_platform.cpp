#include "utils.cpp"
#include <Windows.h>

global_variable bool running = true;

struct Render_State {
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

#include "renderer.cpp"
#include "platform_common.cpp"
#include "game.cpp"

/**
 * Callback for the Window
 * Docs: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-callwindowproca
 */
LRESULT CALLBACK window_callback(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	LRESULT result = 0;

	// Depending on the content of the message received through the window, we stop running the game.
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
		} break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			render_state.width = rect.right - rect.left;
			render_state.height = rect.bottom - rect.top;

			int buffer_size = render_state.width * render_state.height * (sizeof(u32));

			if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
			render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT |MEM_RESERVE, PAGE_READWRITE);

			// Docs of bitmap_info: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmap_infoheader
			render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
			render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
			render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
			render_state.bitmap_info.bmiHeader.biPlanes = 1;
			render_state.bitmap_info.bmiHeader.biBitCount = 32;
			render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;

		} break;

		default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		} break;
	}
	return result;
}

/**
 * This is the application entrypoint for Windows.
 * Docs: https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-winmain
 */
int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {
	/**
	 * Create a Window Class.
	 * Docs: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassa?redirectedfrom=MSDN
	 * Docs about window syles: https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
	 */
	WNDCLASS
		window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_callback;

	// Register that Class (docs: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerclassw)
	RegisterClass(&window_class);

	// Create the Window (docs: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowa)
	HWND window = CreateWindowA(
		"Game Window Class",
		"My First Game",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1200,
		720,
		0, 
		0,
		hInstance,
		0
	);
	

	// Game loop
	run_game(window);
}