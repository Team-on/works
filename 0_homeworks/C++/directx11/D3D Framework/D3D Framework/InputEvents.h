#pragma once
#include "InputCodes.h"

namespace dxFramework{
	namespace Input{
		struct MouseEvent{
			int x;
			int y; 
			MouseEvent(int nx, int ny) : x(nx), y(ny){}
		};

		struct MouseEventClick : public MouseEvent{
			const eMouseKeyCodes btn;
			MouseEventClick(eMouseKeyCodes b, int nx, int ny) : MouseEvent(nx, ny), btn(b){}
		};

		struct MouseEventWheel : public MouseEvent{
			int wheel;
			MouseEventWheel(int nwheel, int nx, int ny) : MouseEvent(nx, ny), wheel(nwheel){}
		};

		struct KeyEvent{
			const wchar_t wc;
			const eKeyCodes code;
			KeyEvent(wchar_t c, eKeyCodes kc) : wc(c), code(kc){}
		};
	}
}