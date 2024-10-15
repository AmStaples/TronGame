#include <Windows.h>
#include "utils.cpp"

struct Render_State {
	int height, width;
	void* memory;
	BITMAPINFO bitmapinfo;
};

global_variable Render_State render_state;

#include "platform_common.cpp"
#include "renderer.cpp"
#include "game.cpp"
/*
Since we include renderer.cpp AFTER creating render_state, the renderer.cpp can use render_state without passing variables.
*/
global_variable bool running = true;


#define process_button(b, vk)\
				case vk: { \
				input.buttons[b].is_down = is_down; \
					input.buttons[b].changed = true; \
				}break;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
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

			int buffer_size = render_state.width * render_state.height * sizeof(u32);

			if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
			render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			render_state.bitmapinfo.bmiHeader.biSize = sizeof(render_state.bitmapinfo.bmiHeader);
			render_state.bitmapinfo.bmiHeader.biWidth = render_state.width;
			render_state.bitmapinfo.bmiHeader.biHeight = render_state.height;
			render_state.bitmapinfo.bmiHeader.biPlanes = 1;
			render_state.bitmapinfo.bmiHeader.biBitCount = 32;
			render_state.bitmapinfo.bmiHeader.biCompression = BI_RGB;
			
	} break;
	
	default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	//Create window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window";
	window_class.lpfnWndProc = window_callback;

	//Register Class
	RegisterClass(&window_class);
	//Create Window
	HWND window = CreateWindow(window_class.lpszClassName, L"My First Game!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	while (running) {
		//inputs
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
		
			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

				

				switch (vk_code) {
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);

				}
			} break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}

			
		}


		//Simulate - All game functions will be done here. It simulates what happens and what should be shown.
		simulate_game(&input);
		
		
		
		



		//Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);
	}
};