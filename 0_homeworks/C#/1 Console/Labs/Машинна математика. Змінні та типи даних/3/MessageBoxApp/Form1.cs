using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MessageBoxApp {
	public partial class Form1 : Form {
		public Form1() {
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e) {
			MessageBox.Show($"{byte.MinValue} {byte.MaxValue}");
		}

		private void button2_Click(object sender, EventArgs e) {
			MessageBox.Show($"{sbyte.MinValue} {sbyte.MaxValue}");
		}

		private void button3_Click(object sender, EventArgs e) {
			MessageBox.Show($"{short.MinValue} {short.MaxValue}");
		}

		private void button4_Click(object sender, EventArgs e) {
			MessageBox.Show($"{ushort.MinValue} {ushort.MaxValue}");
		}

		private void button5_Click(object sender, EventArgs e) {
			MessageBox.Show($"{int.MinValue} {int.MaxValue}");
		}

		private void button8_Click(object sender, EventArgs e) {
			MessageBox.Show($"{uint.MinValue} {uint.MaxValue}");
		}

		private void button7_Click(object sender, EventArgs e) {
			MessageBox.Show($"{long.MinValue} {long.MaxValue}");
		}

		private void button6_Click(object sender, EventArgs e) {
			MessageBox.Show($"{ulong.MinValue} {ulong.MaxValue}");
		}
	}
}
