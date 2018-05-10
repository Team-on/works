using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeStudio {
	static class Singletones {
		public static StudioSettings settings { get; private set; }

		public static DownWindow downWindow { get; private set; }
		public static CodeWindow codeWindow { get; private set; }
		public static LeftWindow leftWindow { get; private set; }
		public static RightWindow rightWindow { get; private set; }
		public static CodeStudioMain codeStudioMain { get; private set; }

		public static void SetWindows(DownWindow down, LeftWindow left, RightWindow right, CodeWindow center, CodeStudioMain main) {
			downWindow = down;
			leftWindow = left;
			rightWindow = right;
			codeWindow = center;
			codeStudioMain = main;

			settings = new StudioSettings();
		}
	}
}
