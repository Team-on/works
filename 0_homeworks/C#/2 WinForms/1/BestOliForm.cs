using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1 {
	public partial class BestOliForm : Form {
		double dailySum = 0;
		Timer timer = new Timer();
		public BestOliForm() {
			InitializeComponent();
			BenzinValue.SelectedIndex = 0;
			timer.Interval = 10;
			timer.Enabled = false;
			timer.Tick += delegate (object sender, EventArgs e) {
				var res = MessageBox.Show("Розпочати роботу з новим клієнтом?", "BestOil", MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button1, MessageBoxOptions.DefaultDesktopOnly);
				timer.Stop();
				if (res != DialogResult.Yes)
					timer.Start();
				else {
					dailySum += double.Parse(oplateVse.Text);
					kolvoBox.Text = summaBox.Text = "0,00";
					checkBox1.Checked = checkBox2.Checked = checkBox3.Checked = checkBox4.Checked = false;
					textBox5.Enabled = textBox6.Enabled = textBox7.Enabled = textBox8.Enabled = false;
					textBox5.Text = textBox6.Text = textBox7.Text = textBox8.Text = "0";
					BenzinValue.SelectedIndex = 0;
					summa.Checked = false;
					kolvo.Checked = true;
				}
			};
		}

		void CalcPriceZapravka(object sender, EventArgs e) {
			if (kolvo.Checked) {
				if (double.TryParse(kolvoBox.Text, out double res)) {
					if(res != 0)
						oplataBenzin.Text = string.Format($"{double.Parse(BenzinPrice.Text) * res:0.##}");
					else 
						oplataBenzin.Text = "0,00";
				}
				else
					oplataBenzin.Text = "0,00";
			}
			else if (summa.Checked) {
				if (double.TryParse(summaBox.Text, out double res)) {
					if (res != 0)
						oplataBenzin.Text = string.Format($"{res / double.Parse(BenzinPrice.Text):0.##}");
					else
						oplataBenzin.Text = "0,00";
				}
				else
					oplataBenzin.Text = "0,00";
			}
		}

		void ChangeZapravkaStyle(object sender, EventArgs e) {
			if (kolvo.Checked) {
				summaBox.Enabled = false;
				summaBox.Text = "0,00";
				kolvoBox.Enabled = true;
				oplataText.Text = "До оплати";
				oplataLabel.Text = "грн";
			}
			else {
				kolvoBox.Enabled = false;
				summaBox.Enabled = true;
				kolvoBox.Text = "0,00";
				oplataText.Text = "До видачі";
				oplataLabel.Text = "Л";
			}
			CalcPriceZapravka(null, null);
		}

		private void BenzinValue_SelectedIndexChanged(object sender, EventArgs e) {
			switch (BenzinValue.SelectedIndex) {
			case 0:
			BenzinPrice.Text = "10,40";
			break;
			case 1:
			BenzinPrice.Text = "11,45";
			break;
			case 2:
			BenzinPrice.Text = "13,55";
			break;
			case 3:
			BenzinPrice.Text = "9,05";
			break;
			default:
			BenzinPrice.Text = "0,00";
			break;
			}
			CalcPriceZapravka(sender, e);
		}

		private void checkBox1_Click(object sender, EventArgs e) {
			CheckBox c = sender as CheckBox;
			TextBox t;
			if (c.Text == checkBox1.Text)
				t = textBox5;
			else if (c.Text == checkBox2.Text)
				t = textBox6;
			else if (c.Text == checkBox3.Text)
				t = textBox7;
			else
				t = textBox8;
			t.Enabled = c.Checked;
			t.Text = "0";
		}

		void RecalcCafePrice(object sender, EventArgs e) {
			double res = 0;
			if (textBox5.Enabled && int.TryParse(textBox5.Text, out int a))
				res += double.Parse(textBox1.Text) * double.Parse(textBox5.Text);
			if (textBox6.Enabled && int.TryParse(textBox6.Text, out int b))
				res += double.Parse(textBox2.Text) * double.Parse(textBox6.Text);
			if (textBox7.Enabled && int.TryParse(textBox7.Text, out int c))
				res += double.Parse(textBox3.Text) * double.Parse(textBox7.Text);
			if (textBox8.Enabled && int.TryParse(textBox8.Text, out int d))
				res += double.Parse(textBox4.Text) * double.Parse(textBox8.Text);
			oplataKafe.Text = res.ToString();
		}

		private void textBox5_KeyPress(object sender, KeyPressEventArgs e) {
			if (!(Char.IsDigit(e.KeyChar) || char.IsControl(e.KeyChar)))
				e.Handled = true;
		}

		private void summaBox_KeyPress(object sender, KeyPressEventArgs e) {
			if ((e.KeyChar == ',' || e.KeyChar == '.') && !(sender as TextBox).Text.Contains(','))
				e.KeyChar = ',';
			else if (!(Char.IsDigit(e.KeyChar) || char.IsControl(e.KeyChar)))
				e.Handled = true;
		}

		void RecalcFinalPrice(object sender, EventArgs e) {
			double.TryParse(oplataKafe.Text, out double all);
			double benz;
			if(kolvo.Checked)
				double.TryParse(oplataBenzin.Text, out benz);
			else
				double.TryParse(summaBox.Text, out benz);
			all += benz;
			oplateVse.Text = string.Format($"{all:0,##}");
		}

		private void button1_Click(object sender, EventArgs e) {
			timer.Enabled = true;
		}

		private void BestOliForm_FormClosing(object sender, FormClosingEventArgs e) {
			MessageBox.Show("Виручка: " + dailySum.ToString());
		}
	}
}
