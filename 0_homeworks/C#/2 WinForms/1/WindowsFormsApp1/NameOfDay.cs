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
	public partial class NameOfDay : Form {
		public NameOfDay() {
			InitializeComponent();
		}

		private void NameOfDay_Load(object sender, EventArgs e) {

		}

		private void monthCalendar1_DateChanged(object sender, DateRangeEventArgs e) {
			string txt = null;
			switch (e.Start.DayOfWeek) {
			case DayOfWeek.Sunday:
			txt = "Неділя";
			break;
			case DayOfWeek.Monday:
			txt = "Понеділок";
			break;
			case DayOfWeek.Tuesday:
			txt = "Вівторок";
			break;
			case DayOfWeek.Wednesday:
			txt = "Середа";
			break;
			case DayOfWeek.Thursday:
			txt = "Четвер";
			break;
			case DayOfWeek.Friday:
			txt = "Пятниця";
			break;
			case DayOfWeek.Saturday:
			txt = "Субота";
			break;
			}
			day.Text = txt;
		}
	}
}
