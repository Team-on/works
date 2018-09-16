#include "stdafx.h"
//TODO: Вияснити чому неможна підключати в порядку Window -> (WindowDescription InputManager), а лише навпаки
#include "WindowDescription.h"
#include "InputManager.h"
#include "Window.h"
#include "Log.h"

namespace dxFramework{
	namespace Render{
		Window::Window(){

		}

		bool Window::Create(const WindowDescription & desc){

			return false;
		}

		void Window::SetInputManager(Input::InputManager * inputmgr){

		}

		void Window::RunEvent(){

		}

		void Window::Close(){

		}

		LRESULT Window::WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam){

			return LRESULT();
		}


		void Window::UpdateWindowState(){

		}



		LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam){
			return LRESULT();
		}
	}
}