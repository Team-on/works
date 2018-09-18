#include "stdafx.h"
#include "WindowDescription.h"

namespace dxFramework{
	namespace Render{
		WindowDescription::WindowDescription() :
			title(L""),
			width(640),
			height(480),
			posx(GetSystemMetrics(SM_CXSCREEN) / 2 - 320 /*width / 2*/),
			posy(GetSystemMetrics(SM_CYSCREEN) / 2 - 240 /*height / 2*/),
			isResizing(true){
			
		}
	}
}