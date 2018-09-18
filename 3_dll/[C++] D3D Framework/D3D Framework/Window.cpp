#include "stdafx.h"
#include "Window.h"
#include "Log.h"
#include "macros.h"

using namespace dxFramework::Util;

namespace dxFramework{
	namespace Render{
		Window *Window::wndthis = nullptr;


		Window::Window() :
			desc(WindowDescription()),
			inputManager(nullptr),
			hwnd(NULL),
			isExit(false),
			isActive(true),
			windowState(None),
			isResize(false){
			if(!wndthis)
				wndthis = this;
			else
				Log::Error("Window already created. Framework didnt support more than 1 window");
		}

		bool Window::Create(const WindowDescription & _desc){
			Log::Debug("Window create");
			desc = _desc;

			WNDCLASSEXW wnd;
			wnd.cbSize = sizeof(WNDCLASSEXW);
			wnd.style = CS_HREDRAW | CS_VREDRAW;
			wnd.lpfnWndProc = StaticWndProc;
			wnd.cbClsExtra = 0;
			wnd.cbWndExtra = 0;
			wnd.hInstance = 0;
			wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
			wnd.hIconSm = wnd.hIcon;
			wnd.hCursor = LoadCursor(0, IDC_ARROW);
			wnd.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
			wnd.lpszMenuName = NULL;
			wnd.lpszClassName = L"D3D11F";

			if(!RegisterClassEx(&wnd)){
				Log::Error("Cant refister window");
				return false;
			}

			RECT rect = { 0, 0, desc.width, desc.height };
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW | WS_VISIBLE, FALSE);

			hwnd = CreateWindowEx(NULL, wnd.lpszClassName, desc.title.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
								  /*static_cast<long>(*/desc.posx/*)*/,  /*static_cast<long>(*/desc.posy/*)*/,
								  rect.right - rect.left, rect.bottom - rect.top,
								  NULL, NULL, NULL, NULL);

			if(!hwnd){
				Log::Error("Не удалось создать окно");
				return false;
			}

			ShowWindow(hwnd, SW_SHOW);
			UpdateWindow(hwnd);

			return true;
		}

		void Window::SetInputManager(Input::InputManager * inputmgr){
			this->inputManager = inputmgr;
			UpdateWindowState();
		}

		void Window::RunEvent(){
			MSG msg;
			while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		void Window::Close(){
			if(hwnd){
				DestroyWindow(hwnd);
				hwnd = nullptr;
				Log::Debug("Window close");
			}
			else
				Log::Debug("Window already closed");
		}

		LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
			switch(msg){
			case WM_CREATE:
				return NULL;

			case WM_CLOSE:
				isExit = true;
				return NULL;

			case WM_ACTIVATE:
				isActive = LOWORD(wparam) != WA_INACTIVE;
				return NULL;

			case WM_MOVE:
				desc.posx = LOWORD(lparam);
				desc.posy = HIWORD(lparam);
				UpdateWindowState();
				return NULL;

			case WM_SIZE:
				if(!desc.isResizing)
					return NULL;

				desc.width = LOWORD(lparam);
				desc.height = HIWORD(lparam);
				isResize = true;

				switch(wparam){
				case SIZE_MINIMIZED:
					isActive = false;
					windowState = Minimized;
					break;
				case SIZE_MAXIMIZED:
					isActive = true;
					windowState = Maximized;
					break;
				case SIZE_RESTORED:
					isActive = true;
					windowState = None;
					break;
				}
				UpdateWindowState();
				return NULL;

			case WM_MOUSEMOVE: case WM_LBUTTONUP: case WM_LBUTTONDOWN: case WM_MBUTTONUP: case WM_MBUTTONDOWN: case WM_RBUTTONUP: case WM_RBUTTONDOWN: case WM_MOUSEWHEEL: case WM_KEYDOWN: case WM_KEYUP:
				if(inputManager)
					inputManager->Run(msg, wparam, lparam);
				return NULL;
			}


			return DefWindowProcW(hwnd, msg, wparam, lparam);
		}


		void Window::UpdateWindowState(){
			RECT rect;
			rect.left = desc.posx;
			rect.top = desc.posy;
			rect.right = desc.width;
			rect.bottom = desc.height;
			if(inputManager)
				inputManager->SetWindowRect(rect);
		}



		LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam){
			return Window::Get()->WndProc(hwnd, nMsg, wParam, lParam);
		}
	}
}