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
				foreach (var i in result) 
					listBox1.Items.Add((Path.GetExtension(i) == ""? "Directory\t" : "File\t") + i);
				listBox1.EndUpdate();
			}
		}
	}
}
