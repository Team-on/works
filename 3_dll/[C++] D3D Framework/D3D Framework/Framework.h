#pragma once
#include "Window.h"
#include "Render.h"
#include "InputManager.h"
#include "Log.h"


namespace dxFramework{
	namespace Framework{
		class Framework{
		public:
			Framework();
			~Framework();

			bool Init();
			void Run();
			void Close();

			void SetRender(Render::Render *render){ this->SetRender = render; }
			void AddInputListener(Input::InputListener *listener);
		
		protected:
			bool Frame();

			Render::Window *window;
			Render::Render *render;
			Input::InputManager *inputManager;
			Util::Log log;
			bool isInit;
		};
	}
}
