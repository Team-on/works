using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using static System.Windows.Forms.DialogResult;

namespace WindowsFormsApp1 {
	public partial class Form1 : Form {
		public Form1() {
			InitializeComponent();
			Text = "Main";
		}

		void f1() {
			Text = "resume";
			string rezume = @"Задание 1
Вывести на экран свое(краткое!!!) резюме с помощью последова-
тельности MessageBox’ов(числом не менее трех).Причем на заголовке
последнего должно отобразиться среднее число символов на странице
(общее количество символов в резюме / количество MessageBox’ов). ";
			string len = (rezume.Length / 3).ToString();

			MessageBox.Show(rezume.Substring(0, rezume.Length / 3), len, MessageBoxButtons.OK);
			MessageBox.Show(rezume.Substring(rezume.Length / 3, rezume.Length / 3), len, MessageBoxButtons.OK);
			MessageBox.Show(rezume.Substring(rezume.Length / 3 * 2), len, MessageBoxButtons.OK);
		}

		void f2() {
			/*
             Написать функцию, которая «угадывает» задуманное пользова-
телем число от 1 до 2000. Для запроса к пользователю использовать
MessageBox. После того, как число отгадано, необходимо вывести
количество запросов, потребовавшихся для этого, и предоставить
пользователю возможность сыграть еще раз, не выходя из программы
(MessageBox’ы оформляются кнопками и значками соответственно
ситуации). 
              */
			Text = "task2";

			ushort num = 1000, min = 1, max = 2000;
			byte cnt;
			DialogResult res;

			do {
				cnt = 0;
				while (true) {
					num = (ushort)((max + min) / 2);
					++cnt;
					res = MessageBox.Show("mb this: " + num.ToString(), "number", MessageBoxButtons.YesNo);
					if (res == Yes) {
						MessageBox.Show("Win. " + cnt.ToString() + " times.", "number", MessageBoxButtons.OK);
						break;
					}
					res = MessageBox.Show("Number more than " + num.ToString(), "number", MessageBoxButtons.YesNo);
					if (res == Yes)
						min = num;
					else
						max = num;
				}
			} while (MessageBox.Show("One more time?", "number", MessageBoxButtons.YesNo) == DialogResult.Yes);

		}

		private void Form1_Activated(object sender, EventArgs e) {
		}

		private void button1_Click(object sender, EventArgs e) {
			f1();
			Text = "Main";
		}

		private void button2_Click(object sender, EventArgs e) {
			f2();
			Text = "Main";
		}

		private void Form1_Load(object sender, EventArgs e) {

		}

		private void button3_Click(object sender, EventArgs e) {
			//using (T3 f = new T3()) {
			new T3().Show();
			//f.Dispose();
			//}
		}

		private void button6_Click(object sender, EventArgs e) {
			new staticRectangles().Show();
		}

		private void button5_Click(object sender, EventArgs e) {
			new MovableStatic().Show();
		}

		private void button8_Click(object sender, EventArgs e) {

		}

		private void button7_Click(object sender, EventArgs e) {

		}

		private void button4_Click(object sender, EventArgs e) {
			new NameOfDay().Show();
		}
	}
}
