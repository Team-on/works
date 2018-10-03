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
			if (System.IO.File.Exists(textBox.Text)) {
				Program.fileLocker.AddFile(textBox.Text);
				listBox.Items.Add(textBox.Text);
				textBox.Text = Properties.Settings.Default.TextBoxStandart;
				textBox.ForeColor = Color.Gray;
			}
			else {
				MessageBox.Show("File not exist", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1);
			}
		}

		private void LockListWindow_FormClosing(object sender, FormClosingEventArgs e) {
			if (e.CloseReason != CloseReason.ApplicationExitCall) {
				e.Cancel = true;
				this.Hide();
			}
		}

		private void LockListWindow_Activated(object sender, EventArgs e) {
			foreach (var i in Properties.Settings.Default.Files) {
				if (listBox.Items.Contains(i))
					continue;
				bool isFind = false;
				foreach (var j in listBox.Items) {
					if ((j as string).Contains(i)) {
						isFind = true;
						break;
					}
				}
				if (!isFind)
					listBox.Items.Add(i);
			}
		}

		private void buttonLockback_Click(object sender, EventArgs e) {
			if (listBox.SelectedIndex != -1) {
				Program.fileLocker.Lock(listBox.SelectedIndex);
				if ((listBox.Items[listBox.SelectedIndex] as string)?.Contains("[UNLOCKED] ") ?? false)
					listBox.Items[listBox.SelectedIndex] = (listBox.Items[listBox.SelectedIndex] as string).Substring(11/*"[UNLOCKED] ".Length*/);
				listBox.Refresh();
			}
		}

		private void buttonUnlock_Click(object sender, EventArgs e) {
			if (listBox.SelectedIndex != -1) {
				Program.fileLocker.Unlock(listBox.SelectedIndex);
				if (!((listBox.Items[listBox.SelectedIndex] as string)?.Contains("[UNLOCKED] ") ?? true))
					listBox.Items[listBox.SelectedIndex] = "[UNLOCKED] " + (listBox.Items[listBox.SelectedIndex] as string);
				listBox.Refresh();
			}
		}

		private void buttonRemove_Click(object sender, EventArgs e) {
			if (listBox.SelectedIndex != -1) {
				Program.fileLocker.Remove(listBox.SelectedIndex);
				listBox.Items.RemoveAt(listBox.SelectedIndex);
				listBox.Refresh();
			}
		}

		private void buttonUnlockAll_Click(object sender, EventArgs e) {
			try {
				Program.fileLocker.UnlockAll();
				for (ushort i = 0; i < listBox.Items.Count; ++i)
					if (!((listBox.Items[i] as string)?.Contains("[UNLOCKED] ") ?? true))
						listBox.Items[i] = "[UNLOCKED] " + (listBox.Items[i] as string);
				listBox.Refresh();
			}
			catch (Exception ex) {
				MessageBox.Show(ex.Message);
			}
		}

		private void buttonLockAll_Click(object sender, EventArgs e) {
			try {
				Program.fileLocker.LockAll();
				for (ushort i = 0; i < listBox.Items.Count; ++i)
					if ((listBox.Items[i] as string)?.Contains("[UNLOCKED] ") ?? false)
						listBox.Items[i] = (listBox.Items[i] as string).Substring(11/*"[UNLOCKED] ".Length*/);
				listBox.Refresh();
			}
			catch (Exception ex) {
				MessageBox.Show(ex.Message);
			}
		}
	}
}
