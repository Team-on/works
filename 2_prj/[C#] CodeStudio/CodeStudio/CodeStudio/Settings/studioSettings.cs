using System.Collections.Generic;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System;
using System.Runtime.InteropServices;

namespace CodeStudio {
	class StudioSettings {
		public string CompilerPathCPlusPlus, CompilerPathCSharp;

		public Color DefaultBackground = Color.FromArgb(30, 30, 30),
			DefaultForeground = Color.FromArgb(255, 255, 255),
			DefaultBackgroundText = Color.FromArgb(30, 30, 30);

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
			CompilerPathCSharp = @"C:\Windows\Microsoft.NET\Framework\v4.0.30319\csc.exe";
		}

		public void Save() {

		}

		public void Load() {

		}
	}
}
