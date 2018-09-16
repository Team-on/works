#pragma once

namespace dxFramework{
	namespace Render{
		struct WindowDescription{
			WindowDescription();

			int posx;
			int posy;
			std::wstring title;
			int width;
			int height;
			bool isResizing;
		};
	}
}