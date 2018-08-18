#pragma once
#include "InputEvents.h"

namespace dxFramework{
	namespace Input{
		class InputListener{
		public:
			// если методы возращают true - событие больше никем не обрабатывается

			virtual bool MousePressed(const MouseEventClick &arg){ return false; }
			virtual bool MouseReleased(const MouseEventClick &arg){ return false; }
			virtual bool MouseWheel(const MouseEventWheel &arg){ return false; }
			virtual bool MouseMove(const MouseEvent &arg){ return false; }

			virtual bool KeyPressed(const KeyEvent &arg){ return false; }
			virtual bool KeyReleased(const KeyEvent &arg){ return false; }
		};
	}
}