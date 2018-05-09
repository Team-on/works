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
		static List<CodeTemplateInfo> codeTemplate;
		static TreeNode treeNodeInstalled;

		static FileCreator() {
			codeTemplate = new List<CodeTemplateInfo>();
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

			List<TreeNode> list = new List<TreeNode>(2);

			foreach (var file in files) {
				list.Add(new TreeNode(file.Name.Substring(0, file.Name.LastIndexOf('.'))));

				XmlDocument xml = new XmlDocument();
				xml.Load(file.FullName);


				CodeTemplateInfo codeTemplateInfo = new CodeTemplateInfo();
				foreach (XmlNode i in xml.ChildNodes) {
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


				codeTemplate.Add(codeTemplateInfo);
			}

			node = new TreeNode(folder.Name, list.ToArray());

			return true;
		}

		public FileCreator() {
			InitializeComponent();
			treeView1.Nodes.Add(treeNodeInstalled);
		}
	}

	class CodeTemplateInfo {
		public string ex, type, desct, code;
	}
}
