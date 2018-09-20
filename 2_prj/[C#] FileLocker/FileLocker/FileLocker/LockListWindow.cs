using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FileLocker {
	public partial class LockListWindow : Form {
		public LockListWindow() {
			InitializeComponent();
			textBox.Text = Properties.Settings.Default.TextBoxStandart;
			textBox.ForeColor = Color.Gray;

			//RefilListBox();
		}

		void RefilListBox() {
			listBox.Items.Clear();
			foreach (var i in Properties.Settings.Default.Files)
				listBox.Items.Add(i);
		}

		private void textBox_KeyDown(object sender, KeyEventArgs e) {
			if (textBox.Text == Properties.Settings.Default.TextBoxStandart) {
				textBox.Text = "";
				textBox.ForeColor = Color.Black;
			}
		}

		private void buttonMore_Click(object sender, EventArgs e) {
			if (Program.fileDialog.Value.ShowDialog() == DialogResult.OK) {
				textBox.Text = Program.fileDialog.Value.FileName;
				textBox.ForeColor = Color.Black;
			}
		}

		private void buttonLock_Click(object sender, EventArgs e) {
			Program.fileLocker.AddFile(textBox.Text);
			textBox.Text = Properties.Settings.Default.TextBoxStandart;
			textBox.ForeColor = Color.Gray;
		}

		private void LockListWindow_FormClosing(object sender, FormClosingEventArgs e) {
			if (e.CloseReason != CloseReason.ApplicationExitCall) {
				e.Cancel = true;
				this.Hide();
			}
		}

		private void LockListWindow_Activated(object sender, EventArgs e) {
			RefilListBox();
		}
	}
}
