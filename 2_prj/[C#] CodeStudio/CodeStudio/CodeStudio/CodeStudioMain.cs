using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VistaKeysExtender.WinApi;
 

/*
15:00 В ШАГ зал. презентація софтсерва
*/

namespace CodeStudio {
	public partial class CodeStudioMain : Form {
		CodeWindow codeWindow;
		DownWindow downWindow;
		LeftWindow leftWindow;
		RightWindow rightWindow;
		FileCreator fileCreator = null;

		public CodeStudioMain() {
			InitializeComponent();
			this.KeyPreview = true;

			leftToolStripMenuItem.Checked = rightToolStripMenuItem.Checked = downToolStripMenuItem.Checked = true;

			codeWindow = new CodeWindow {
				MdiParent = this,
				FormBorderStyle = FormBorderStyle.None
			};
			downWindow = new DownWindow { MdiParent = this };
			leftWindow = new LeftWindow { MdiParent = this };
			rightWindow = new RightWindow { MdiParent = this };

			codeWindow.ResizeEnd += ResizeFields;
			downWindow.ResizeEnd += ResizeFields;
			leftWindow.ResizeEnd += ResizeFields;
			rightWindow.ResizeEnd += ResizeFields;

			downWindow.FormClosing += delegate (object s, FormClosingEventArgs eventArgs) {
				eventArgs.Cancel = true;
				downToolStripMenuItem_Click(s, null);
			};
			leftWindow.FormClosing += delegate (object s, FormClosingEventArgs eventArgs) {
				eventArgs.Cancel = true;
				leftToolStripMenuItem_Click(s, null);
			};
			rightWindow.FormClosing += delegate (object s, FormClosingEventArgs eventArgs) {
				eventArgs.Cancel = true;
				rightToolStripMenuItem_Click(s, null);
			};
			this.FormClosing += delegate (object s, FormClosingEventArgs eventArgs) {
				eventArgs.Cancel = false;
			};
		}

		private void CodeStudioMain_Shown(object sender, EventArgs e) {
			codeWindow.Show();
			downWindow.Show();
			leftWindow.Show();
			rightWindow.Show();

			Size size = this.ClientRectangle.Size;
			size.Height -= statusStrip.Height + menuStrip.Height + 4 + toolStrip1.Height;
			size.Width -= 4;

			leftWindow.Size = new Size(size.Width / 5, size.Height);
			leftWindow.Location = new Point(0, 0);

			rightWindow.Size = new Size(size.Width / 5, size.Height);
			rightWindow.Location = new Point(size.Width - rightWindow.Size.Width, 0);

			downWindow.Size = new Size(size.Width - leftWindow.Width - rightWindow.Width,
				size.Height / 5);
			downWindow.Location = new Point(leftWindow.Size.Width, 
				size.Height - downWindow.Height);

			codeWindow.Size = new Size(downWindow.Size.Width, size.Height - downWindow.Height);
			codeWindow.Location = new Point(leftWindow.Size.Width, leftWindow.Location.Y);
		}

		void ResizeFields(object sender, EventArgs e) {
			Size size = this.ClientRectangle.Size;
			size.Height -= statusStrip.Height + menuStrip.Height + 4 + toolStrip1.Height;
			size.Width -= 4;

			if(sender == downWindow)
				ResizeLeft();
			if (sender == downWindow)
				ResizeRight();
			if (sender == leftWindow || sender == rightWindow)
				ResizeDown();
			if (sender == leftWindow || sender == rightWindow || sender == downWindow)
				ResizeCenter();

			leftWindow.Location = new Point(0, 0);
			rightWindow.Location = new Point(size.Width - rightWindow.Size.Width, 0);
			downWindow.Location = new Point((leftToolStripMenuItem.Checked ? leftWindow.Size.Width : 0), size.Height - downWindow.Height);
			codeWindow.Location = new Point(downWindow.Location.X, leftWindow.Location.Y);

			void ResizeLeft() {
				leftWindow.Size = new Size(size.Width - downWindow.Width - rightWindow.Width, size.Height);
				leftWindow.Location = new Point(0, 0);
			}
			void ResizeRight() {
				rightWindow.Size = new Size(size.Width - downWindow.Width - leftWindow.Width, size.Height);
				rightWindow.Location = new Point(size.Width - (rightToolStripMenuItem.Checked ? rightWindow.Width : 0), 0);
			}
			void ResizeDown() {
				downWindow.Size = new Size(size.Width - (leftToolStripMenuItem.Checked?leftWindow.Width:0) - (rightToolStripMenuItem.Checked?rightWindow.Width:0), size.Height - codeWindow.Height);
				downWindow.Location = new Point((leftToolStripMenuItem.Checked?leftWindow.Size.Width:0), size.Height - downWindow.Height);
			}
			void ResizeCenter() {
				codeWindow.Size = new Size(downWindow.Size.Width, size.Height - (downToolStripMenuItem.Checked? downWindow.Height :0));
				codeWindow.Location = new Point(downWindow.Location.X, leftWindow.Location.Y);
			}
		}

		private void fileToolStripMenuItem2_Click(object sender, EventArgs e) {
			if(DialogResult.OK== openFileDialog1.ShowDialog())
				codeWindow.AddFile(openFileDialog1.FileName);
		}

		private void saveToolStripMenuItem_Click(object sender, EventArgs e) {
			codeWindow.SaveCurrentFile();
		}

		private void saveAllToolStripMenuItem_Click(object sender, EventArgs e) {
			codeWindow.SaveAllFiles();
		}

		private void fileToolStripMenuItem1_Click(object sender, EventArgs e) {
			if (fileCreator == null)
				fileCreator = new FileCreator();
			fileCreator.ShowDialog();
			if (fileCreator.IsFileCreated())
				codeWindow.AddNewFile("New code." + fileCreator.GetExtension(), fileCreator.GetCode());
			fileCreator.Reload();
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e) {
			codeWindow.SaveAllFiles();
			this.Close();
		}

		private void leftToolStripMenuItem_Click(object sender, EventArgs e) {
			if (this.leftToolStripMenuItem.Checked) {
				//this.sizeWhenExitLeft = leftWindow.Size;
				//this.locationWhenExitLeft = leftWindow.Location;
				leftWindow.Size = new Size(0, leftWindow.Size.Height);
				leftWindow.Hide();
			}
			else {
				leftWindow.Show();
				//leftWindow.Size = sizeWhenExitLeft;
				//leftWindow.Location = locationWhenExitLeft;
			}
			leftToolStripMenuItem.Checked = !leftToolStripMenuItem.Checked;
			ResizeFields(leftWindow, null);
		}

		private void rightToolStripMenuItem_Click(object sender, EventArgs e) {
			if (this.rightToolStripMenuItem.Checked) {
				//this.sizeWhenExitRight = rightWindow.Size;
				rightWindow.Size = new Size(0, rightWindow.Size.Height);
				//locationWhenExitRight = rightWindow.Location;
				rightWindow.Hide();
			}
			else {
				rightWindow.Show();
				//rightWindow.Size = sizeWhenExitRight;
				//rightWindow.Location = locationWhenExitRight;
			}
			rightToolStripMenuItem.Checked = !rightToolStripMenuItem.Checked;
			ResizeFields(rightWindow, null);
		}

		private void downToolStripMenuItem_Click(object sender, EventArgs e) {
			if (this.downToolStripMenuItem.Checked) {
				//this.sizeWhenExitDown = downWindow.Size;
				downWindow.Size = new Size(codeWindow.Width, 0);
				//locationWhenExitDown = downWindow.Location;
				downWindow.Hide();
			}
			else {
				downWindow.Show();
				//downWindow.Size = sizeWhenExitDown;
				// downWindow.Location= locationWhenExitDown;
			}
			downToolStripMenuItem.Checked = !downToolStripMenuItem.Checked;
			ResizeFields(downWindow, null);
		}

		private void CloseThisTab(object sender, EventArgs e) {
			codeWindow.CloseCurrentTab();
		}

		private void CloseAllTab(object sender, EventArgs e) {
			codeWindow.CloseAllTab();
		}

		private void CloseAllButThisTab(object sender, EventArgs e) {
			codeWindow.CloseAllButThisTab();
		}

		private void CloseAllLeftTab(object sender, EventArgs e) {
			codeWindow.CloseAllLeftTab();
		}

		private void CloseAllRightTab(object sender, EventArgs e) {
			codeWindow.CloseAllRightTab();
		}	
	}
}
