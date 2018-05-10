using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CodeStudio {
	class StudioSettings {
		public string CompilerPathCPlusPlus, CompilerPathCSharp;

		bool wordWarp;
		public bool WordWarp {
			set {
				wordWarp = value;
				Singletones.codeStudioMain.wordWarpToolStripMenuItem.Checked = value;
				Singletones.codeWindow.SetNewWordWarp(value);
			}
			get => wordWarp;
		}

		public int TabLength = 4;

		public StudioSettings() {
			WordWarp = false;
			CompilerPathCPlusPlus = "";
			CompilerPathCSharp = "";
		}
	}
}
