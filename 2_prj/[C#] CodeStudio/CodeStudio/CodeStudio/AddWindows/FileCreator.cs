using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;
using System.Xml;

namespace CodeStudio {
	public partial class FileCreator : Form {
		static TreeNode treeNodeInstalled;
		bool isFileCreated;

		static FileCreator() {
			AddFileTemplates();
		}

		static void AddFileTemplates() {
			List<TreeNode> list = new List<TreeNode>(2);

			DirectoryInfo templates = new DirectoryInfo("FileTemplates");
			foreach (DirectoryInfo folder in templates.GetDirectories()) {
				TreeNode node;
				if (ParseFileTemplates(folder, out node))
					list.Add(node);
			}

			treeNodeInstalled = new TreeNode("Installed", list.ToArray());
			treeNodeInstalled.Expand();
		}

		static bool ParseFileTemplates(DirectoryInfo folder, out TreeNode node) {
			var files = folder.GetFiles();
			node = null;
			if (files.Length == 0)
				return false;

			List<CodeTemplateInfo> list = new List<CodeTemplateInfo>(2);

			List<TreeNode> listNodes = new List<TreeNode>(2);
			foreach (DirectoryInfo fold in folder.GetDirectories()) {
				TreeNode n;
				if (ParseFileTemplates(fold, out n))
					listNodes.Add(n);
			}

			foreach (var file in files) {
				XmlDocument xml = new XmlDocument();
				xml.Load(file.FullName);

				CodeTemplateInfo codeTemplateInfo = new CodeTemplateInfo();
				foreach (XmlNode i in xml.ChildNodes[1].ChildNodes) {
					string name = i.Name.ToLower();
					if (name == "ex")
						codeTemplateInfo.ex = i.InnerText;
					else if (name == "type")
						codeTemplateInfo.type = i.InnerText;
					else if (name == "descr")
						codeTemplateInfo.desct = i.InnerText;
					else if (name == "code")
						codeTemplateInfo.code = i.InnerText;
				}
				codeTemplateInfo.fileName = file.Name;
				list.Add(codeTemplateInfo);
			}

			node = new TreeNode(folder.Name);
			node.Nodes.AddRange(listNodes.ToArray());
			node.Tag = list;

			return true;
		}

		public FileCreator() {
			InitializeComponent();
			foreach (TreeNode i in treeNodeInstalled.Nodes)
				treeView1.Nodes.Add(i);

			treeView1.AfterSelect += delegate (object send, TreeViewEventArgs args) {
				listView.Items.Clear();

				if (args.Node.Tag is List<CodeTemplateInfo>) {
					List<CodeTemplateInfo> info = args.Node.Tag as List<CodeTemplateInfo>;
					foreach (var i in info)
						this.listView.Items.Add(new ListViewItem(i.fileName.Substring(0, i.fileName.LastIndexOf('.'))) { Tag = i });
				}

				if (textBox1.Text != "") 
					textBox1.Text = "";
				button1.Enabled = false;

			};

			listView.SelectedIndexChanged += delegate (object sender, EventArgs ar) {
				if ((sender as ListView).SelectedItems.Count != 0) {
					CodeTemplateInfo i = ((sender as ListView).SelectedItems[0].Tag as CodeTemplateInfo);
					textBox1.Text = "Type: " + i.type + Environment.NewLine + Environment.NewLine + "Description: " + i.desct;
					button1.Enabled = true;
				}
			};

			Reload();
		}

		public void Reload() {
			isFileCreated = button1.Enabled = false;
		}

		public bool IsFileCreated() => isFileCreated;
		public string GetExtension() => (listView.SelectedItems[0].Tag as CodeTemplateInfo).ex;
		public string GetCode() => (listView.SelectedItems[0].Tag as CodeTemplateInfo).code.Trim();
		public CodeTemplateInfo GetCodeTemplateInfo() => (listView.SelectedItems[0].Tag as CodeTemplateInfo);

		private void button1_Click(object sender, EventArgs e) {
			isFileCreated = true;
			this.Close();
		}

		private void listView_MouseDoubleClick(object sender, MouseEventArgs e) {
			button1.PerformClick();
		}

		private void FileCreator_Shown(object sender, EventArgs e) {
			this.Size = new Size(893, 500);
		}
	}

	public class CodeTemplateInfo {
		public string ex, type, desct, code, fileName;
	}
}
