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

		void CreateTab(string path) {
			if (IsOpened(path)) 
				return;

			var a = new TabCodeInfo();
			if (path != null) {
				a.isNew = false;
				a.isSaved = true;
				a.path = path;
				a.name = path.Substring(path.LastIndexOf('\\') + 1);
				a.ReadLinkedFile();
			}
			else {
				a.isNew = true;
				a.isSaved = false;
				a.path = a.name = "New File";
			}

			a.tab.TextChanged += delegate(object s, System.EventArgs args) {
					if (tabControl.SelectedIndex != -1) {
						if (tabCodeInfo[tabControl.SelectedIndex].name[tabCodeInfo[tabControl.SelectedIndex].name.Length - 1] != '*') {
							tabCodeInfo[tabControl.SelectedIndex].name += "*";
							tabCodeInfo[tabControl.SelectedIndex].isSaved = false;
						}
					}
					SetTabTextToRichBoxNames();
			};

			tabCodeInfo.Add(a);

			TabPage tab = new TabPage();
			tab.Controls.Add(a.tab);
			tab.Name = tab.Text = a.name;
			tabControl.Controls.Add(tab);

			tabControl.SelectedIndex = tabControl.TabCount - 1;
			tabControl.TabIndex = 0;
		}

		public void AddFile(string path) {
			CreateTab(path);
		}

		public void AddNewFile() {
			CreateTab(null);
		}

		public void AddNewFile(string tabName, string tabText) {
			AddNewFile();
			tabCodeInfo[tabCodeInfo.Count - 1].name = tabControl.SelectedTab.Text = tabName;
			tabCodeInfo[tabCodeInfo.Count - 1].tab.Text = tabText;
			tabCodeInfo[tabCodeInfo.Count - 1].extensions = tabName.Substring(tabName.LastIndexOf('.') + 1) + " file" + "|*" + tabName.Substring(tabName.LastIndexOf('.'));
		}

		public bool IsOpened(string path) {
			foreach (var i in tabCodeInfo) 
				if (i.path == path)
					return true;
			return false;
		}

		public void SaveCurrentFile() {
			if (tabControl.TabCount != 0) {
				if (tabCodeInfo[tabControl.SelectedIndex].SaveLinkedFile()) {
					if (tabCodeInfo[tabControl.SelectedIndex].name[tabCodeInfo[tabControl.SelectedIndex].name.Length - 1] == '*')
						tabCodeInfo[tabControl.SelectedIndex].name = tabCodeInfo[tabControl.SelectedIndex].name.Substring(0, tabCodeInfo[tabControl.SelectedIndex].name.Length - 1);
				}
				SetTabTextToRichBoxNames();
			}
		}

		public void SaveAllFiles() {
			foreach (var i in tabCodeInfo) {
				if(i.SaveLinkedFile() && i.name[i.name.Length - 1] == '*')
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
			tabControl.Controls.RemoveAt(tabId);
			tabCodeInfo.RemoveAt(tabId);
		}
	}

	class TabCodeInfo {
		static SaveFileDialog saveFileDialog = new SaveFileDialog();

		public string path;
		public string name;
		public bool isNew, isSaved;
		public RichTextBox tab = new RichTextBox() { Dock = DockStyle.Fill };
		public string extensions = "";

		public TabCodeInfo() {
			SetTabWidth(tab, Settings.settings.tabLength);
		}

		public void ReadLinkedFile() {
			using (var t = new StreamReader(path))
				tab.Text = t.ReadToEnd();
			isSaved = true;
		}

		//True if saved
		public bool SaveLinkedFile() {
			if (isNew) {
				if(extensions != "")
				saveFileDialog.Filter = extensions;
				if (saveFileDialog.ShowDialog() == DialogResult.OK) {
					path = saveFileDialog.FileName;
					using (var writer = new StreamWriter(path))
						writer.Write(tab.Text);
					isNew = false;
					name = path.Substring(path.LastIndexOf('\\') + 1);
					isSaved = true;
				}
			}
			else {
				using (var writer = new StreamWriter(path))
					writer.Write(tab.Text);
				isSaved = true;
			}
			return isSaved;
		}


		// set tab stops to a width of 4
		private const int EM_SETTABSTOPS = 0x00CB;

		[DllImport("User32.dll", CharSet = CharSet.Auto)]
		public static extern IntPtr SendMessage(IntPtr h, int msg, int wParam, int[] lParam);

		public static void SetTabWidth(RichTextBox textbox, int tabWidth) {
			//Graphics graphics = textbox.CreateGraphics();
			//var characterWidth = (int)graphics.MeasureString("M", textbox.Font).Width;
			//SendMessage(textbox.Handle, EM_SETTABSTOPS, 1,
			//			new int[] { tabWidth * characterWidth });
			SendMessage(textbox.Handle, EM_SETTABSTOPS, 1,
			new int[] { tabWidth * 4 });
		}
		//END of tab with set
	}
}
