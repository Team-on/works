using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.ServiceModel;
using Client.ServiceReference1;

namespace Client {
	public partial class Form1 : Form {
		Service1Client proxy;

		public Form1() {
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e) {
			proxy.Login(textBox1.Text);
		}

		private void button2_Click(object sender, EventArgs e) {
			proxy.Logout(textBox1.Text);
		}

		private void button3_Click(object sender, EventArgs e) {
			proxy.SendText(textBox2.Text);
		}

		private void Form1_Load(object sender, EventArgs e) {
			proxy = new Service1Client(new InstanceContext(new ClientCallback() {form=this }));
		}
	}
}
