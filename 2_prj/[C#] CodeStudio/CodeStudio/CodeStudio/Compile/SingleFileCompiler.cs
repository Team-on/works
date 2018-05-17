using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace CodeStudio {
	class SingleFileCompiler {
		public void CompileFileAndRun(string path) {
			Compile(path);
			RunExe(path);
		}

		public Process Compile(string path) {
			if (!File.Exists(path))
				return null;

			Process rezult = null;

			string ex = path.Substring(path.LastIndexOf('.') + 1);
			if (ex == "cs")
				rezult = CompileCSharp(path);

			if (rezult == null)
				return rezult;


			while (!rezult.HasExited) {
			Singletones.downWindow.CompilerOutput.Text = "Start time: " + rezult.StartTime.ToLongTimeString() + "\n";
				Singletones.downWindow.CompilerOutput.Text += rezult.StandardOutput.ReadToEnd();
				System.Threading.Thread.Sleep(100);
			}
			Singletones.downWindow.CompilerOutput.Text += "End time: " + DateTime.Now.ToLongTimeString();

			return rezult;
		}

		public void RunExe(string path) {
			string exePath = path.Substring(0, path.LastIndexOf('.')) + ".exe";
			//System.Windows.Forms.MessageBox.Show("PreRun");
			if (!File.Exists(exePath))
				return;

			//System.Windows.Forms.MessageBox.Show("Run");
			var runProcess = System.Diagnostics.Process.Start(exePath);
		}

		Process CompileCSharp(string path) {
			if (!File.Exists(Singletones.settings.CompilerPathCSharp))
				return null;

			string exePath = path.Substring(0, path.LastIndexOf('.')) + ".exe";
			var template = CompilerProcessTemplate(path);
			template.FileName = Singletones.settings.CompilerPathCSharp;
			template.Arguments =  " /target:exe";
			template.Arguments += " /out:" + exePath;
			template.Arguments += " " + path;
			//System.Windows.Forms.MessageBox.Show(exePath);
			//System.Windows.Forms.MessageBox.Show(template.Arguments);
			var runProcess = System.Diagnostics.Process.Start(template);

			return runProcess;
		}

		ProcessStartInfo CompilerProcessTemplate(string path) {
			return new System.Diagnostics.ProcessStartInfo(path) {
				CreateNoWindow = true,
				UseShellExecute = false,
				RedirectStandardOutput = true
			};
		}
	}
}
