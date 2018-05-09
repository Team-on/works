using System.Collections.Generic;
using System.IO;
using System.Drawing;
using System.Windows.Forms;

namespace CodeStudio {
	public partial class CodeWindow : Form {
		List<TabCodeInfo> tabCodeInfo;

		public CodeWindow() {
			InitializeComponent();
			tabCodeInfo = new List<TabCodeInfo>(4);
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
		}

		public void AddFile(string path) {
			CreateTab(path);
		}

		public void AddNewFile() {
			CreateTab(null);
		}

		public bool IsOpened(string path) {
			foreach (var i in tabCodeInfo) 
				if (i.path == path)
					return true;
			return false;
		}

		public void SaveCurrentFile() {
			if (tabControl.TabCount != 0) {
				tabCodeInfo[tabControl.SelectedIndex].SaveLinkedFile();
				if (tabCodeInfo[tabControl.SelectedIndex].name[tabCodeInfo[tabControl.SelectedIndex].name.Length - 1] == '*')
					tabCodeInfo[tabControl.SelectedIndex].name = tabCodeInfo[tabControl.SelectedIndex].name.Substring(0, tabCodeInfo[tabControl.SelectedIndex].name.Length - 1);
				SetTabTextToRichBoxNames();
			}
		}

		public void SaveAllFiles() {
			foreach (var i in tabCodeInfo) {
				i.SaveLinkedFile();
				if (i.name[i.name.Length - 1] == '*') 
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


		public void ReadLinkedFile() {
			using (var t = new StreamReader(path))
				tab.Text = t.ReadToEnd();
			isSaved = true;
		}

		public void SaveLinkedFile() {
			if (isNew) {
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
		}
	}
}
