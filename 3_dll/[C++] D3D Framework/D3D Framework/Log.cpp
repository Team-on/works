#include "stdafx.h"
#include "Log.h"

namespace dxFramework{
	namespace Util{

		Log *Log::instance = nullptr;

		Log::Log(){
			if(!instance){
#ifdef LOG_PRINT_FILE
				file = nullptr;
#endif
				instance = this;
				_Init();
			}
			else
				Error("Try to create log while another log existing.");
		}


		Log::~Log(){
			_Close();
		}

		void Log::Print(const char * message, ...){
			va_list args;
			va_start(args, message);
			int len = _vscprintf(message, args) + 1;
			char *buffer = static_cast<char*>(malloc(len * sizeof(char)));
			vsprintf_s(buffer, len, message, args);
			instance->_Print("", buffer);
			va_end(args);
			free(buffer);
		}

		void Log::Debug(const char * message, ...){
#ifdef _DEBUG
			va_list args;
			va_start(args, message);
			int len = _vscprintf(message, args) + 1;
			char *buffer = static_cast<char*>(malloc(len * sizeof(char)));
			vsprintf_s(buffer, len, message, args);
			instance->_Print("DEBUG: ", buffer);
			va_end(args);
			free(buffer);
#endif
		}

		void Log::Error(const char * message, ...){
			va_list args;
			va_start(args, message);
			int len = _vscprintf(message, args) + 1;
			char *buffer = static_cast<char*>(malloc(len * sizeof(char)));
			vsprintf_s(buffer, len, message, args);
			instance->_Print("ERROR: ", buffer);
			va_end(args);
			free(buffer);
		}

		void Log::_Init(){
			setlocale(LC_ALL, "rus");

#ifdef LOG_PRINT_FILE
			if(!fopen_s(&file, LOG_NAME, "w")){
				char timer[9], date[9];
				_strtime_s(timer, 9);
				_strdate_s(date, 9);
				fprintf(file, "Create log: %s %s\n", date, timer);
				fprintf(file, "---------------------------------------\n\n");
			}
			else{
				printf("Error while creating log...\n");
				file = nullptr;
			}
#endif 
		}

		void Log::_Close(){
#ifdef LOG_PRINT_FILE
			if(!file)
				return;

			char timer[9], date[9];
			_strtime_s(timer, 9);
			_strdate_s(date, 9);
			fprintf(file, "---------------------------------------\n\n");
			fprintf(file, "Close log: %s %s\n", date, timer);
			fclose(file);
			file = nullptr;
#endif 
		}

		void Log::_Print(const char *levtext, const char *text){
			char timer[9];
			_strtime_s(timer, 9);
#ifdef LOG_PRINT_CONSOLE
			printf("%s %s: %s", timer, levtext, text);
#endif 
#ifdef LOG_PRINT_FILE
			if(file){
				fprintf(file ,"%s %s%s", timer, levtext, text);
				fflush(file);
			}
#endif 
		}
	}
}