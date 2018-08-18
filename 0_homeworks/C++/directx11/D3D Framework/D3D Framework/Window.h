#pragma once
#include "InputManager.h"

namespace dxFramework{
	namespace Render{
		struct WindowDescription{
			WindowDescription() :
				title(L""),
				width(640),
				height(480),
				posX(200),
				posY(20),
				isResizing(true){
			}

			int posX;
			int posY;
			std::wstring title;
			int width;
			int height;
			bool isResizing;
		};

		class Window{
		public:
			Window();

			static Window* Get(){ return m_wndthis; }

			// ������� ����
			bool Create(const WindowDescription &desc);

			// ��������� ������� ����
			void RunEvent();

			// ������� ����.
			void Close();

			void SetInputManager(Input::InputManager *inputmgr);

			HWND GetHWND() const{ return m_hwnd; }
			int Window::GetLeft() const{ return m_desc.posx; }
			int Window::GetTop() const{ return m_desc.posy; }
			int Window::GetWidth() const{ return m_desc.width; }
			int Window::GetHeight() const{ return m_desc.height; }
			// ������� ��������� ����
			const std::wstring& GetCaption() const{ return m_desc.caption; }

			// ��������, ���� �� ��������� � ������
			bool IsExit() const{ return m_isexit; }
			// �������� �� ���������� ����
			bool IsActive() const{ return m_active; }
			// �������� �� ��������� ����
			// ��������������: ����� ������ ��������� ���� �� ��������� �������
			bool IsResize(){
				bool ret = m_isresize;
				m_isresize = false;
				return ret;
			}

			// ��������� �������
			LRESULT WndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
		private:
			void m_UpdateWindowState();

			static Window *m_wndthis;

			WindowDescription m_desc;	// �������� ����
			Input::InputManager *m_inputmgr;
			HWND m_hwnd;		// ���������� ����	
			bool m_isexit;		// ���� ���������� � ������� ������	
			bool m_active;		// ���� �������?
			bool m_minimized;
			bool m_maximized;
			bool m_isresize;	// ���� ���� �������� ������
		};

		// ��������� �������
		static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

	}
}