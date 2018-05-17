using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CodeStudio {
	public partial class DownWindow : Form {
		public DownWindow() {
			InitializeComponent();
		}

		private void DownWindow_Shown(object sender, EventArgs e) {
			tabPageCompiler.ForeColor = Singletones.settings.DefaultForeground;
			tabPageCompiler.BackColor = Singletones.settings.DefaultBackground;
			this.ForeColor = Singletones.settings.DefaultForeground;
			this.BackColor = Singletones.settings.DefaultBackground;

			this.FormBorderStyle = FormBorderStyle.SizableToolWindow;

			this.tabPageCompiler.ForeColor = Singletones.settings.DefaultForeground;
			this.tabPageCompiler.BackColor = Singletones.settings.DefaultBackground;

			this.CompilerOutput.ForeColor = Singletones.settings.DefaultForeground;
			this.CompilerOutput.BackColor = Singletones.settings.DefaultBackgroundText;
		}

		private void CompilerOutput_TextChanged(object sender, EventArgs e) {

		}

		private void CompilerOutput_KeyUp(object sender, KeyEventArgs e) {
			e.Handled = true;
			e.SuppressKeyPress = true;
		}
	}
}
