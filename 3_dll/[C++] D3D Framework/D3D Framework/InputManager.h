#pragma once
#include "InputCodes.h"
#include "InputEvents.h"
#include "InputListener.h"

namespace dxFramework{
	namespace Input{
		class InputManager{
		public:
			void Init();
			void Close();

			void Run(const UINT &msg, WPARAM wParam, LPARAM lParam);

			void AddListener(InputListener *listener);

			void SetWindowRect(const RECT &winrect);

		private:
			void EventMouseMove();
			void EventMouseButton(const eMouseKeyCodes keyCode, bool isPressed);
			void EventMouseWheel(short value);
			void EventKey(const eKeyCodes keyCode, const wchar_t charValue, bool isPressed);

			std::list<InputListener *> listeners;
			RECT windowRect;
			int currX, currY, mouseWheel;
		};
	}
}

