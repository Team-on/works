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
	public partial class RightWindow : Form {
		bool ClickOnNode = false;

		public RightWindow() {
			InitializeComponent();

			Explorer.ContextMenuStrip = explorerContextMenu;
		}

		private void Explorer_DoubleClick(object sender, EventArgs e) {
			TreeView treeView = sender as TreeView;
			TabCodeInfo choosenTab = treeView.SelectedNode.Tag as CodeStudio.TabCodeInfo;

			if (!Singletones.codeWindow.IsOpened(choosenTab.path))
				Singletones.codeWindow.LoadFileFromExplorer(choosenTab);
		}

		private void Explorer_MouseClick(object sender, MouseEventArgs e) {
			if (e.Button == MouseButtons.Right) 
				ClickOnNode = Explorer.GetNodeAt(e.X, e.Y) != null ? true : false;
		}

		private void toolStripMenuItem1_Click(object sender, EventArgs e) {
			if (ClickOnNode) {
				TabCodeInfo choosenTab = Explorer.SelectedNode.Tag as CodeStudio.TabCodeInfo;
				if (choosenTab != null) {
					if (!Singletones.codeWindow.IsOpened(choosenTab.path))
						Singletones.codeWindow.LoadFileFromExplorer(choosenTab);
				}
				ClickOnNode = false;
			}
		}

		private void toolStripMenuItem2_Click(object sender, EventArgs e) {
			if (ClickOnNode) {
				TabCodeInfo choosenTab = Explorer.SelectedNode.Tag as CodeStudio.TabCodeInfo;
				if (choosenTab != null) {
					Singletones.codeWindow.CloseTabByTab(choosenTab);
					Explorer.SelectedNode.Remove();
				}
				ClickOnNode = false;
			}
		}

		private void RightWindow_Shown(object sender, EventArgs e) {
			tabPageExplorer.ForeColor = tabPageProperties.ForeColor =
			Explorer.ForeColor = Singletones.settings.DefaultForeground;
			tabPageExplorer.BackColor = tabPageProperties.BackColor =
			Explorer.BackColor = Singletones.settings.DefaultBackground;
			this.ForeColor = Singletones.settings.DefaultForeground;
			this.BackColor = Singletones.settings.DefaultBackground;

			this.FormBorderStyle = FormBorderStyle.SizableToolWindow;

			CodeStudio.StyleChanger.SetContexMenuStripStyle(explorerContextMenu);
		}
	}
}
