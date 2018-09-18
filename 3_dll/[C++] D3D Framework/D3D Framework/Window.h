#pragma once


namespace dxFramework{
	namespace Render{
		//����������: ����� ���� ������ ���� ���� Window.
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
			// �������� �� ��������� ����
			// ��������������: ����� ������ ��������� ���� �� ��������� �������
			bool IsResize(){
				bool ret = isResize;
				isResize = false;
				return ret;
			}

			// ��������� �������
			/*virtual*/ LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		private:
			enum WindowState : char {None, Minimized, Maximized};

			void UpdateWindowState();

			static Window *wndthis;

			WindowDescription desc;			// �������� ����
			Input::InputManager *inputManager;
			HWND hwnd;						// ���������� ����	
			bool isExit;					// ���� ���������� � ������� ������	
			bool isActive;					// ���� �������?
			WindowState windowState;
			bool isResize;					// ���� ���� �������� ������
		};

		// ��������� �������
		//static ������ ��� ������� ����� ������ � ����� Window.h � Window.cpp
		static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
	}
}