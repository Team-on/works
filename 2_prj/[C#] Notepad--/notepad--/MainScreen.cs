using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace notepad__ {
	public partial class MainScreen : Form {
		string allowedFormats = "Text|*.txt|All|*.*";
		string path = "none";
		bool saved = false;

		public MainScreen() {
			InitializeComponent();
			openFileDialog1.Filter = allowedFormats;
			saveFileDialog1.Filter = allowedFormats;
			this.Size = new Size(System.Windows.Forms.Screen.PrimaryScreen.WorkingArea.Size.Width / 2, System.Windows.Forms.Screen.PrimaryScreen.WorkingArea.Size.Height / 2);
		}

		void Open(string _path) {
			mainText.Text = "";
			saved = true;
			path = _path;
			Text = _path.Substring(_path.LastIndexOf('\\') + 1);
			using (System.IO.StreamReader file = new System.IO.StreamReader(path)) 
				mainText.Text = file.ReadToEnd();
		}

		void Save() {
			if(path != "none")
				SaveAs(path);
		}

		void SaveAs(string str) {
			saved = true;
			using (System.IO.StreamWriter file = new System.IO.StreamWriter(str))
				for (int i = 0; i < mainText.Lines.Length; ++i) 
					file.WriteLine(mainText.Lines[i]);
		}

		void New(string str) {
			path = (string) str.Clone();
			Text = path.Substring(path.LastIndexOf('\\') + 1);
			SaveAs(str);
		}

		DialogResult ExitWithoutSave() {
			if (path != "none" || mainText.Text.Length > 0)
				return MessageBox.Show(this, "Do u want 2 save " + (path == "none" ? "Untiled" : path) + " ?", "Notepad--", MessageBoxButtons.YesNoCancel);
			return DialogResult.No;
		}

		void Exit(object sender, EventArgs e) {
			if (!saved) {
				DialogResult res = ExitWithoutSave();
				if (res != DialogResult.None) {
					if (res == DialogResult.No)
						this.Close();
					if (res == DialogResult.Yes) {
						if (path != "none")
							Save();
						else
							saveAsToolStripMenuItem_Click(sender, e);
						this.Close();
					}
				}
			}
		}

		private void MainScreen_FormClosing(object sender, FormClosingEventArgs e) {
			if (!saved) {
				DialogResult res = ExitWithoutSave();
				if (res != DialogResult.None) {
					if (res == DialogResult.Yes) {
						if (path != "none")
							Save();
						else
							saveAsToolStripMenuItem_Click(sender, e);
					}
					if (res == DialogResult.Cancel)
						e.Cancel = true;
				}
			}
		}

		private void mainText_KeyDown(object sender, KeyEventArgs e) {
			MainScreen_KeyDown(sender, e);
		}

		private void newToolStripMenuItem_Click(object sender, EventArgs e) {
			DialogResult res = saveFileDialog1.ShowDialog();
			if(res == DialogResult.OK) 
				New(saveFileDialog1.FileName);
			
		}

		private void openToolStripMenuItem_Click(object sender, EventArgs e) {
			DialogResult res = openFileDialog1.ShowDialog();
			if (res == DialogResult.OK) 
				Open(openFileDialog1.FileName);
		}

		private void saveToolStripMenuItem_Click(object sender, EventArgs e) {
			if(path != "none")
				Save();
			else saveAsToolStripMenuItem_Click(null, null);
		}

		private void saveAsToolStripMenuItem_Click(object sender, EventArgs e) {
			DialogResult res = saveFileDialog1.ShowDialog();
			if (res == DialogResult.OK)
				SaveAs(saveFileDialog1.FileName);
		}

		private void MainScreen_KeyDown(object sender, KeyEventArgs e) {
			if(e.Control == true) {
				switch (e.KeyCode) {
				case Keys.N:
					newToolStripMenuItem_Click(sender, e);
				break;
				case Keys.O:
					openToolStripMenuItem_Click(sender, e);
				break;
				case Keys.S:
					saveToolStripMenuItem_Click(sender, e);
				break;
				default:
				if (!saved || mainText.Text.Length > 0)
					saved = false;
				break;
				}
			}
		}
	}
}
