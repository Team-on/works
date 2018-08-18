#include "stdafx.h"
#include "InputManager.h"
#include "Log.h"

namespace dxFramework{
	namespace Input{
		void InputManager::Init(){
			mouseWheel = currX = currY = 0;
			dxFramework::Util::Log::Debug("Init inputManager");
		}

		void InputManager::Close(){
			if(!listeners.empty())
				listeners.clear();
			dxFramework::Util::Log::Debug("Init inputManager");
		}

		void InputManager::Run(const UINT & msg, WPARAM wParam, LPARAM lParam){
			if(listeners.empty())
				return;

			eKeyCodes KeyIndex;
			wchar_t buffer[1];
			BYTE lpKeyState[256];

			EventMouseMove();
			switch(msg){
			case WM_KEYDOWN:
				KeyIndex = static_cast<eKeyCodes>(wParam);
				GetKeyboardState(lpKeyState);
				ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, buffer, 1, 0);
				EventKey(KeyIndex, buffer[0], true);
				break;
			case WM_KEYUP:
				KeyIndex = static_cast<eKeyCodes>(wParam);
				GetKeyboardState(lpKeyState);
				ToUnicode(wParam, HIWORD(lParam) & 0xFF, lpKeyState, buffer, 1, 0);
				EventKey(KeyIndex, buffer[0], false);
				break;
			case WM_LBUTTONDOWN:
				EventMouseButton(MOUSE_LEFT, true);
				break;
			case WM_LBUTTONUP:
				EventMouseButton(MOUSE_LEFT, false);
				break;
			case WM_RBUTTONDOWN:
				EventMouseButton(MOUSE_RIGHT, true);
				break;
			case WM_RBUTTONUP:
				EventMouseButton(MOUSE_RIGHT, false);
				break;
			case WM_MBUTTONDOWN:
				EventMouseButton(MOUSE_MIDDLE, true);
				break;
			case WM_MBUTTONUP:
				EventMouseButton(MOUSE_MIDDLE, false);
				break;
			case WM_MOUSEWHEEL:
				EventMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
				break;
			}
		}

		void dxFramework::Input::InputManager::AddListener(InputListener * listener){
			listeners.push_back(listener);
		}

		void InputManager::SetWindowRect(const RECT & winrect){
			windowRect.left = winrect.left;
			windowRect.right = winrect.right;
			windowRect.top = winrect.top;
			windowRect.bottom = winrect.bottom;
		}


		void InputManager::EventMouseMove(){
			POINT newPos;
			GetCursorPos(&newPos);

			newPos.x -= windowRect.left;
			newPos.y -= windowRect.top;

			if(currX == newPos.x && currY == newPos.y)
				return;

			currX = newPos.x;
			currY = newPos.y;

			for(auto it = listeners.begin(); it != listeners.end(); ++it)
				if(*it && (*it)->MouseMove(MouseEvent(currX, currY)))
					return;
		}

		void InputManager::EventMouseButton(const eMouseKeyCodes keyCode, bool isPressed){
			bool(InputListener::*mouseFunc)(const MouseEventClick&);
			if(isPressed)
				mouseFunc = &InputListener::MousePressed;
			else
				mouseFunc = &InputListener::MouseReleased;

			for(auto it = listeners.begin(); it != listeners.end(); ++it)
				if(*it && ((*it)->*mouseFunc)(MouseEventClick(keyCode, currX, currY)))
					return;
		}

		void InputManager::EventMouseWheel(short value){
			if(mouseWheel == value)
				return;

			mouseWheel = value;

			for(auto it = listeners.begin(); it != listeners.end(); ++it)
				if(*it && (*it)->MouseWheel(MouseEventWheel(mouseWheel, currX, currY)))
					return;
		}

		void InputManager::EventKey(const eKeyCodes keyCode, const wchar_t charValue, bool isPressed){
			bool(InputListener::*keyFunc)(const KeyEvent&);
			if(isPressed)
				keyFunc = &InputListener::KeyPressed;
			else
				keyFunc = &InputListener::KeyReleased;

			for(auto it = listeners.begin(); it != listeners.end(); ++it)
				if(*it && ((*it)->*keyFunc)(KeyEvent(charValue, keyCode)))
					return;
		}
	}
}