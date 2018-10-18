using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsClient {
	public partial class Form1 : Form {
		Converter.ConverterClient converter;


		public Form1() {
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e) {
			converter = new Converter.ConverterClient();
		}

		private void button1_Click(object sender, EventArgs e) {
			double val = 0;

			if(!double.TryParse(textBox1.Text, out val)) {
				MessageBox.Show("Cant parse number!");
				return;
			}

			textBox2.Text = "";
			textBox3.Text = "";
			textBox4.Text = "";

			if (radioButton1.Checked) {
				var rez = converter.LinearMeasure(val);
				textBox2.Text = $"Inch:\t{rez.Inch}";
				textBox3.Text = $"Foot:\t{rez.Foot}";
				textBox4.Text = $"Yard:\t{rez.Yard}";
			}
			else if (radioButton2.Checked) {
				var rez = converter.CelsiusToFahrenheit(val);
				textBox2.Text = $"Celsius:\t{rez.Celsius}";
				textBox3.Text = $"Fahrenheit:\t{rez.Fahrenheit}";
			}
			else if (radioButton3.Checked) {
				var rez = converter.FahrenheitToCelsius(val);
				textBox2.Text = $"Celsius:\t{rez.Celsius}";
				textBox3.Text = $"Fahrenheit: {rez.Fahrenheit}";
			}
		}

		private void textBox1_KeyPress(object sender, KeyPressEventArgs e) {
			if (!(
				e.KeyChar == 8 ||
				char.IsDigit(e.KeyChar) ||
				e.KeyChar == ',' || 
				e.KeyChar == '.'
			))
				e.Handled = true;
		}

		private void Form1_FormClosed(object sender, FormClosedEventArgs e) {
			converter?.Close();
		}

		private void textBox1_KeyDown(object sender, KeyEventArgs e) {
			//if (!(
			//	e.KeyCode == Keys.Back || 
			//	(Keys.D0 <= e.KeyCode && e.KeyCode <= Keys.D9) || 
			//	(Keys.NumPad0 <= e.KeyCode && e.KeyCode <= Keys.NumPad9)
			//))
			//	e.Handled = true;
		}
	}
}
