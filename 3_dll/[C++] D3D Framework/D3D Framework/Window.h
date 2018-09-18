#pragma once


namespace dxFramework{
	namespace Render{
		//ѕримечание: может быть только одно окно Window.
		class Window{
		public:
			static Window* Get(){ return wndthis; }

			Window();
			bool Create(const WindowDescription &desc);
			void SetInputManager(Input::InputManager *inputmgr);

			void RunEvent();

			void Close();

			HWND GetHWND() const{ return hwnd; }
			int GetLeft() const{ return desc.posx; }
			int GetTop() const{ return desc.posy; }
			int GetWidth() const{ return desc.width; }
			int GetHeight() const{ return desc.height; }
			const std::wstring& GetTitle() const{ return desc.title; }
			bool IsExit() const{ return isExit; }
			bool IsActive() const{ return isActive; }
			// сообщает об изменении окна
			// предупреждение: после вызова оповещает окно об обработке событи€
			bool IsResize(){
				bool ret = isResize;
				isResize = false;
				return ret;
			}

			// обработка событий
			/*virtual*/ LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		private:
			enum WindowState : char {None, Minimized, Maximized};

			void UpdateWindowState();

			static Window *wndthis;

			WindowDescription desc;			// описание окна
			Input::InputManager *inputManager;
			HWND hwnd;						// дескриптор окна	
			bool isExit;					// флаг сообщающий о событии выхода	
			bool isActive;					// окно активно?
			WindowState windowState;
			bool isResize;					// если окно изменило размер
		};

		// обработка событий
		//static значит что функци€ видна только в файле Window.h и Window.cpp
		static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	}
}