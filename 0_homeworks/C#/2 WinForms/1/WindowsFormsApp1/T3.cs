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
	public partial class T3 : Form {
		/* Представьте, что у вас на форме есть прямоугольник, границы ко-
 торого на 10 пикселей отстоят от границ рабочей области формы.Не -
 обходимо создать следующие обработчики:
 ¦ Обработчик нажатия левой кнопки мыши, который выво-
 дит сообщение о том, где находится текущая точка: вну -
 три прямоугольника, снаружи, на границе прямоугольника.
  Если при нажатии левой кнопки мыши была нажата кнопка
 Control(Ctrl), то приложение должно закрываться;
 ¦ Обработчик нажатия правой кнопки мыши, который вы-
 водит в заголовок окна информацию о размере клиентской
 (рабочей) области окна в виде: Ширина = x, Высота = y, где
 x и y – соответствующие параметры вышего окна;
 ¦ Обработчик перемещения указателя мыши в пределах ра -
 бочей области, который должен выводить в заголовок окна
 текущие координаты мыши x и y. 
 */
		public T3() {
			InitializeComponent();
			Text = "task3";
		}

		private void Form1_MouseClick(object sender, MouseEventArgs e) {
			
			if (e.Button == MouseButtons.Right) {
				Text = string.Format($"Ширина = {this.ClientSize.Width.ToString() }, Высота = {this.ClientSize.Height.ToString()}");
			}
			else if (e.Button == MouseButtons.Left) {
				if (Form.ModifierKeys == Keys.ControlKey || Form.ModifierKeys == Keys.Control) {
					//Close();
					this.Dispose();
					return;
				}

				int x = e.X, y = e.Y;
				string text = "";
				if (x > 10 && y > 10 && x < ClientSize.Width - 10 && y < ClientSize.Height - 10)
					text = "Inside";
				else if ((x < 10 || y < 10) || (x > ClientSize.Width - 10 || y > ClientSize.Height - 10))
					text = "Outside";
				else
					text = "On border";

				MessageBox.Show(text, x.ToString() + "  " + y.ToString());
			}
		}

		private void T3_Activated(object sender, EventArgs e) {
		}

		private void T3_MouseMove(object sender, MouseEventArgs e) {
			Text = string.Format($"x = {e.X}, y = {e.Y}");
			Form1_MouseClick(sender, e);
		}
	}
}
