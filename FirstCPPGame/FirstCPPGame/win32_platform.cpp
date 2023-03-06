#include <Windows.h>
#include "utils.h"
#include "render.h"
#include "game.h"

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
			Game::GAME_RUNNING = false;
		} break;

		case WM_SIZE: {
			RECT rect;
			GetClientRect(hwnd, &rect);
			Render::RENDER_STATE.WND_WIDTH = rect.right - rect.left;
			Render::RENDER_STATE.WND_HEIGHT = rect.bottom - rect.top;

			int buffer_size = Render::RENDER_STATE.WND_WIDTH * Render::RENDER_STATE.WND_HEIGHT * (sizeof(Utils::u32));

			if (Render::RENDER_STATE.WND_MEMORY) VirtualFree(Render::RENDER_STATE.WND_MEMORY, 0, MEM_RELEASE);
			Render::RENDER_STATE.WND_MEMORY = VirtualAlloc(0, buffer_size, MEM_COMMIT |MEM_RESERVE, PAGE_READWRITE);

			// Docs of bitmap_info: https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmap_infoheader
			Render::RENDER_STATE.WND_BITMAPINFO.bmiHeader.biSize = sizeof(Render::RENDER_STATE.WND_BITMAPINFO.bmiHeader);
			Render::RENDER_STATE.WND_BITMAPINFO.bmiHeader.biWidth = Render::RENDER_STATE.WND_WIDTH;
			Render::RENDER_STATE.WND_BITMAPINFO.bmiHeader.biHeight = Render::RENDER_STATE.WND_HEIGHT;
			Render::RENDER_STATE.WND_BITMAPINFO.bmiHeader.biPlanes = 1;
			Render::RENDER_STATE.WND_BITMAPINFO.bmiHeader.biBitCount = 32;
			Render::RENDER_STATE.WND_BITMAPINFO.bmiHeader.biCompression = BI_RGB;

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
	Game::runGame(&window);
}
