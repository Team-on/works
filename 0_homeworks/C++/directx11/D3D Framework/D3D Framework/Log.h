#pragma once
#include "compileSettings.h"

namespace dxFramework{
	namespace Util{
		class Log{
		public:
			Log();
			~Log();

			static void Print(const char *message, ...);
			static void Debug(const char *message, ...);
			static void Error(const char *message, ...);

		private:
			static Log *instance;

			void _Init();
			void _Close();
			void _Print(const char *levtext, const char *text);

#ifdef LOG_PRINT_FILE
			FILE *file;
#endif
		};
	}
}
