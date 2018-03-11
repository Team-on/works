#include "precompiledHeaders.h"
#include "input_my.h"


input_my::input_my(){
	GetConsoleMode(HANDLE_INPUT, &_oldConsoleMode);
	SetConsoleMode(HANDLE_INPUT, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);
}


input_my::~input_my(){
	SetConsoleMode(HANDLE_INPUT, _oldConsoleMode);
}

int input_my::ReadInput() {
	GetNumberOfConsoleInputEvents(HANDLE_INPUT, &info);
	if (!info)
		return ERROR_INPUT_NO_INPUT;

	if (ReadConsoleInputA(HANDLE_INPUT, &input, 1, &info)) {
		FlushConsoleInputBuffer(HANDLE_INPUT);
		switch (input.EventType){
		case KEY_EVENT:
			if (input.Event.KeyEvent.bKeyDown) {
				if (input.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
					return input.Event.KeyEvent.wVirtualKeyCode;
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
					return input.Event.KeyEvent.wVirtualKeyCode;
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_UP)
					return input.Event.KeyEvent.wVirtualKeyCode;
				else if (input.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
					return input.Event.KeyEvent.wVirtualKeyCode;
				else 
					return input.Event.KeyEvent.uChar.AsciiChar;
				
			}
		break;

		case MOUSE_EVENT:
			if (input.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				settings.SetClickPos(input.Event.MouseEvent.dwMousePosition);
				return input.Event.MouseEvent.dwButtonState;
			}
			else if (input.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
				settings.SetClickPos(input.Event.MouseEvent.dwMousePosition);
				return input.Event.MouseEvent.dwButtonState;
			}
			else
				return ERROR_INPUT_UNTRACKED_INPUT_MOUSE;
		break;

		case WINDOW_BUFFER_SIZE_EVENT:
		case FOCUS_EVENT: 
		case MENU_EVENT: 
		return ERROR_INPUT_UNTRACKED_INPUT;
		default:
		return ERROR_INPUT_UNKNOWN_EVENT_TYPE;
		}
	}
	return ERROR_INPUT_NO_INPUT;
}