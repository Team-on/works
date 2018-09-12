using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TaskManager {
	public partial class Form1 : Form {
		List<Process> process;

		public Form1() {
			process = new List<Process>();

			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e) {
			
		}
	}
}
