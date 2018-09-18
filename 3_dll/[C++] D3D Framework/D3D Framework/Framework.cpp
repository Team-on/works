#include "stdafx.h"
#include "Framework.h"
#include "WindowDescription.h"
#include "macros.h"

namespace dxFramework{
	namespace Framework{
		Framework::Framework() :
			window(nullptr),
			render(nullptr),
			inputManager(nullptr),
			isInit(false)
		{

		}


		Framework::~Framework(){

		}

		bool Framework::Init(){
			if(!(window = new Render::Window())){
				Util::Log::Error("Cant allocate memory for Window");
				return false;
			}

			Render::WindowDescription desc;
			if(!window->Create(desc)){
				Util::Log::Error("Cant create window");
				return false;
			}

			if(!(inputManager = new Input::InputManager())){
				Util::Log::Error("Cant allocate memory for InputManager");
				return false;
			}
			inputManager->Init();
			window->SetInputManager(inputManager);

			if(!render){
				Util::Log::Error("Render == nullptr. Use SetRender() before Init()");
				return false;
			}
			if(render->Init(window->GetHWND())){
				Util::Log::Error("Cant initialize render");
				return false;
			}

			isInit = true;
			return true;
		}

		void Framework::Run(){
			if(isInit)
				while(Frame());
		}

		void Framework::Close(){
			isInit = false;
			_CLOSE(render);
			_CLOSE(inputManager);
			_CLOSE(window);
		}

		void Framework::AddInputListener(Input::InputListener * listener){
			if(inputManager)
				inputManager->AddListener(listener);
		}

		bool Framework::Frame(){
			if(!window->IsActive())
				return true;

			if(window->IsExit())
				return false;

			//TODO: Може це треба перед IsActive та IsExit.
			window->RunEvent();

			if(window->IsResize()){
				//TODO:
			}

			if(!render->Draw())
				return false;

			return true;
		}
	}
}