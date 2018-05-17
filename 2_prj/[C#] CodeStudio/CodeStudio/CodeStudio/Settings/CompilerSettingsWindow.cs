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
	public partial class CompilerSettingsWindow : Form {
		public CompilerSettingsWindow() {
			InitializeComponent();
			this.comboBox1.SelectedIndex = 0;
			this.FormClosing += delegate (object sender, FormClosingEventArgs e) {
				SaveCurrPath();
				this.comboBox1.SelectedIndex = 0;
			};

		}

		void SaveCurrPath() {
			if (textBox1.Text != "") {
				if (comboBox1.SelectedIndex == 0)
					Singletones.settings.CompilerPathCSharp = textBox1.Text;
				else if (comboBox1.SelectedIndex == 1)
					Singletones.settings.CompilerPathCPlusPlus = textBox1.Text;
			}
		}

		private void comboBox1_SelectedIndexChanged(object sender, EventArgs e) {
			if(comboBox1.SelectedIndex == 0)
				textBox1.Text = Singletones.settings.CompilerPathCSharp;
			else if (comboBox1.SelectedIndex == 1)
				textBox1.Text = Singletones.settings.CompilerPathCPlusPlus;
			else
				textBox1.Text = "";
		}

		static OpenFileDialog openFileDialog = new OpenFileDialog() { Filter= "Compilers|*.exe" };
		private void button1_Click(object sender, EventArgs e) {
			if (DialogResult.OK == openFileDialog.ShowDialog() && openFileDialog.CheckPathExists) {
				textBox1.Text = openFileDialog.FileName;
				SaveCurrPath();
			}
		}

		private void textBox1_TextChanged(object sender, EventArgs e) {
			if (System.IO.File.Exists(textBox1.Text))
				SaveCurrPath();
		}
	}
}
