using System.Collections.Generic;
using System.IO;
using System.Drawing;
using System.Windows.Forms;
using System;
using System.Runtime.InteropServices;

namespace CodeStudio {
	public partial class CodeWindow : Form {
		List<TabCodeInfo> tabCodeInfo;

		public CodeWindow() {
			InitializeComponent();
			tabCodeInfo = new List<TabCodeInfo>(4);
			this.KeyPreview = true;
		}

		protected override bool ProcessDialogKey(Keys keyData) {
			switch (keyData) {
			case Keys.Tab:
			var box = (tabControl.SelectedTab.Controls[0] as RichTextBox);
			if (box is null)
				return true;

			box.SelectedText += '\t';

			return true;
			default:
				return base.ProcessDialogKey(keyData);
			}
		}

		void CreateTab(string pathArg, CodeTemplateInfo codeTemplateInfo) {
			if (IsOpened(pathArg)) 
				return;

			TabCodeInfo codeInfo  = new TabCodeInfo(pathArg, codeTemplateInfo);

			codeInfo.tab.TextChanged += delegate(object s, System.EventArgs args) {
				AddOrRemAsteriksToName();

				void AddOrRemAsteriksToName() {
					if (tabControl.SelectedIndex != -1) {
						if (tabCodeInfo[tabControl.SelectedIndex].name[tabCodeInfo[tabControl.SelectedIndex].name.Length - 1] != '*') {
							tabCodeInfo[tabControl.SelectedIndex].name += "*";
							tabCodeInfo[tabControl.SelectedIndex].isSaved = false;
						}

					}
					SetTabTextToRichBoxNames();
				}
			};

			tabCodeInfo.Add(codeInfo);

			TreeNode solutionNode = new TreeNode(codeInfo.name) { Tag = codeInfo };
			solutionNode.Tag = codeInfo;
			codeInfo.solutionExprorerNode = solutionNode;

			CrateTabInTAbControl(codeInfo);

			tabControl.SelectedIndex = tabControl.TabCount - 1;

			Singletones.rightWindow.Explorer.Nodes.Add(solutionNode);

			codeInfo.syntaxChecker?.HighlightText(codeInfo.tab);
		}

		public void AddFile(string path) {
			CreateTab(path, null);
		}

		public void AddNewFile(CodeTemplateInfo codeTemplateInfo) {
			CreateTab(null, codeTemplateInfo);
		}

		void CrateTabInTAbControl(TabCodeInfo codeInfo) {
			TabPage tab = new TabPage();
			tab.BackColor = Singletones.settings.DefaultBackground;
			tab.ForeColor = Singletones.settings.DefaultForeground;
			tab.Controls.Add(codeInfo.tab);
			tab.Name = tab.Text = codeInfo.name;
			tabControl.Controls.Add(tab);
			tab.TextChanged += delegate (object s, System.EventArgs args) {
				codeInfo.solutionExprorerNode.Text = tab.Text;
			};

			tabControl.SelectedIndex = tabControl.TabCount - 1;
		}

		public void LoadFileFromExplorer(TabCodeInfo codeInfo) {
			tabCodeInfo.Add(codeInfo);
			CrateTabInTAbControl(codeInfo);
		}

		public bool IsOpened(string path) {
			foreach (var i in tabCodeInfo) 
				if (i.path == path)
					return true;
			return false;
		}

		public void SaveCurrentFile() {
			if (tabControl.TabCount != 0) {
				if (tabCodeInfo[tabControl.SelectedIndex].SaveLinkedFile(true) &&
					tabCodeInfo[tabControl.SelectedIndex].name[tabCodeInfo[tabControl.SelectedIndex].name.Length - 1] == '*'
					) {
					tabCodeInfo[tabControl.SelectedIndex].name = tabCodeInfo[tabControl.SelectedIndex].name.Substring(0, tabCodeInfo[tabControl.SelectedIndex].name.Length - 1);
				}
				SetTabTextToRichBoxNames();
			}
		}

		public void SaveAllFiles() {
			foreach (var i in tabCodeInfo) {
				if(i.SaveLinkedFile())
					if(i.name[i.name.Length - 1] == '*')
					i.name = i.name.Substring(0, i.name.Length - 1);
			}
			SetTabTextToRichBoxNames();
		}

		void SetTabTextToRichBoxNames() {
			for (int i = 0; i < tabControl.Controls.Count; ++i)
				if (tabControl.Controls[i].Text != tabCodeInfo[i].name)
					tabControl.Controls[i].Text = tabCodeInfo[i].name;
		}

		public void CloseAllTab() {
			int length = tabControl.TabCount;
			while (length-- != 0)
				CloseTab(0);
		}

		public void CloseAllButThisTab() {
			int length = tabControl.TabCount - 1;
			while (length-- != 0)
				if(tabControl.SelectedIndex != 0)
					CloseTab(0);
				else
					CloseTab(1);
		}

		public void CloseAllLeftTab() {
			int length = tabControl.SelectedIndex;
			while (length-- != 0)
				CloseTab(0);
		}

		public void CloseAllRightTab() {
			int length = tabControl.TabCount - tabControl.SelectedIndex - 1;
			while (length-- != 0)
				CloseTab(tabControl.TabCount - 1);
		}

		public void CloseCurrentTab() {
			CloseTab(tabControl.SelectedIndex);
		}

		void CloseTab(int tabId) {
			if (tabId < 0 || tabId >= tabControl.TabCount)
				return;

			if (tabCodeInfo[tabId].isDefault) {
				Singletones.rightWindow.Explorer.Nodes.Remove(tabCodeInfo[tabId].solutionExprorerNode);
				tabControl.Controls.RemoveAt(tabId);
				tabCodeInfo.RemoveAt(tabId);
				return;
			}

			if (tabCodeInfo[tabId].isSaved) {
				tabControl.Controls.RemoveAt(tabId);
				tabCodeInfo.RemoveAt(tabId);
				return;
			}

			if(tabCodeInfo[tabId].SaveLinkedFile()) {
				tabControl.Controls.RemoveAt(tabId);
				tabCodeInfo.RemoveAt(tabId);
				return;
			}

		}

		public void CloseTabByTab(TabCodeInfo tabId) {
			if (tabCodeInfo.Contains(tabId)) {
				int index = tabCodeInfo.IndexOf(tabId);
				CloseTab(index);
				GC.Collect();
			}
		}

		public void SetNewWordWarp(bool wordWarp) {
			foreach (var i in this.tabCodeInfo) {
				i.tab.WordWrap = wordWarp;
			}
		}

		private void CodeWindow_Shown(object sender, EventArgs e) {
			this.ForeColor = Singletones.settings.DefaultForeground;
			this.BackColor = Singletones.settings.DefaultBackground;
		}

		private void tabControl_ControlAdded(object sender, ControlEventArgs e) {
			if ((sender as TabControl).Controls.Count == 1)
				(sender as TabControl).Visible = true;
		}

		private void tabControl_ControlRemoved(object sender, ControlEventArgs e) {
			if ((sender as TabControl).Controls.Count == 0) {
				(sender as TabControl).Visible = false;
				Singletones.downWindow.Activate();
			}
		}

		public void CompileCurrentFile() {
			if (tabControl.TabCount != 0) 
				tabCodeInfo[tabControl.SelectedIndex].CompileSingleFile();
		}

		public void RunCurrentFile() {
			if (tabControl.TabCount != 0)
				tabCodeInfo[tabControl.SelectedIndex].RunLinkedExe();
		}
	}
}
