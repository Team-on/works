using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace CodeStudio {
	class SingleFileCompiler {
		public void CompileFileAndRun(string path) {
			if (path == null)
				return;

			string ex = path.Substring(path.LastIndexOf('.') + 1);
			if (ex == "cpp")
				CompileCpp(path);
			if (ex == "cs")
				CompileCSharp(path);

			RunExe(path);
		}

		void CompileCpp(string path) {

		}

		void CompileCSharp(string path) {

		}

		void RunExe(string path) {

		}
	}
}
