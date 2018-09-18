#pragma once

namespace dxFramework{
	namespace Render{
		class Render{
		public:
			Render();
			virtual ~Render();

			virtual bool Init(HWND hwnd) = 0;
			virtual bool Draw() = 0;
			virtual void Close() = 0;
		};
	}
}
