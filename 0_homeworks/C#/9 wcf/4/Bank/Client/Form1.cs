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
using Client.BankServiceReference;

namespace Client {
	public partial class Form1 : Form {
		BankClient proxy;
		int userNum = -1;

		public Form1() {
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e) {
			if (int.TryParse(textBox1.Text, out int initialMoney)) 
				userNum = proxy.CreateAccount(initialMoney);
		}

		private void button2_Click(object sender, EventArgs e) {
			if(userNum != -1 && int.TryParse(textBox2.Text, out int money))
				proxy.Withdraw(money, userNum);
		}

		private void button3_Click(object sender, EventArgs e) {
			if (userNum != -1)
				textBox3.Text = proxy.GetAccountInfo(userNum).ToString();
		}

		private void Form1_Load(object sender, EventArgs e) {
			proxy = new BankClient(new InstanceContext(new ClientCallback() {form=this }));
		}

		private void textBox2_TextChanged(object sender, EventArgs e) {

		}

		private void textBox1_TextChanged(object sender, EventArgs e) {

		}
	}
}
