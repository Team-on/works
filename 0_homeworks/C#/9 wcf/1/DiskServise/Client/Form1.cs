using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client {
	public partial class Form1 : Form {
		public Form1() {
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e) {
			
		}

		private void button1_Click(object sender, EventArgs e) {
			using (DiskServiseLink.DiskServiseClient cl = new DiskServiseLink.DiskServiseClient()) {
				string[] result = cl.GetDiskInfo(textBox1.Text);

				if(result == null) {
					MessageBox.Show("Directory not exist!", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
					return;
				}

				listBox1.Items.Clear();
				listBox1.BeginUpdate();
				listBox1.Items.Add("Directory\t..");
				foreach (var i in result) 
					listBox1.Items.Add((Path.GetExtension(i) == ""? "Directory\t" : "File\t") + i);
				listBox1.EndUpdate();
			}
		}

		private void listBox1_DoubleClick(object sender, EventArgs e) {
			if (listBox1.SelectedItem == null)
				return;

			string path = listBox1.SelectedItem.ToString().Split('\t')[1];

			if (Path.HasExtension(path)) {
				MessageBox.Show("Not a folder!", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}


			if (path == "..") {
				if (textBox1.Text != "D:\\" && textBox1.Text != "C:\\") {
					if (textBox1.Text.Last() == '\\')
						textBox1.Text = textBox1.Text.Substring(0, textBox1.Text.Length - 1);
					textBox1.Text = textBox1.Text.Substring(0, textBox1.Text.LastIndexOf('\\') + 1);
				}
			}
			else {
				if (textBox1.Text.Last() != '\\')
					textBox1.Text += '\\';
				textBox1.Text += path;
			}

			button1_Click(null, null);
		}
	}
}
