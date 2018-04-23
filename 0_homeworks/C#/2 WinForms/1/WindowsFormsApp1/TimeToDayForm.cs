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
	public partial class TimeToDayForm : Form {
		public TimeToDayForm() {
			InitializeComponent();
			second.Checked = true;
			foreach (var i in choose.Controls)
				if(i is RadioButton)
					(i as RadioButton).Click += RecalcTime;
		}

		private void RecalcTime(object sender, EventArgs e) {
			remain.Text = (GetRemainTime()??"ErrorRemainTime") + " " + (GetValueName()??"ErrorValueName");

			string GetRemainTime() {
				if (date.Value.Subtract(DateTime.Now).Seconds <= 0)
					return "0";
				if (year.Checked)
					return Math.Round(date.Value.Subtract(DateTime.Now).TotalDays / 365, 3).ToString();
				if (mounth.Checked)
					//return Math.Round(GetMnthCnt(DateTime.Now, date.Value), 2).ToString(); 
					return GetMnthCnt(DateTime.Now, date.Value).ToString(); 
				if (week.Checked)
					return Math.Round(date.Value.Subtract(DateTime.Now).TotalDays / 7, 2).ToString(); 
				if (day.Checked)
					return Math.Round(date.Value.Subtract(DateTime.Now).TotalDays).ToString();
				if (minute.Checked)
					return Math.Round(date.Value.Subtract(DateTime.Now).TotalMinutes, 2).ToString();
				if (second.Checked)
					return Math.Round(date.Value.Subtract(DateTime.Now).TotalSeconds, 3).ToString();
				return null;
			}


			double GetMnthCnt(DateTime start, DateTime end) {
				DateTime dt1 = new DateTime(start.Year, start.Month, start.Day);
				DateTime dt2 = new DateTime(end.Year, end.Month, end.Day);

				if (dt1 > dt2 || dt1 == dt2)
					return 0;

				double days = (dt2 - dt1).TotalDays;
				double mnt = 0;

				while(days != 0) {
					int inMnt = DateTime.DaysInMonth(dt1.Year, dt1.Month);
					if (days >= inMnt) {
						days -= inMnt;
						++mnt;
						dt1 = dt1.AddMonths(1);
					}
					else {
						mnt += days / inMnt;
						days = 0;
					}
				}

				return mnt;
			}


			string GetValueName() {
				if (year.Checked)
					return "Років";
				if (mounth.Checked)
					return "Міс";
				if (week.Checked)
					return "Тж";
				if (day.Checked)
					return "Дн";
				if (minute.Checked)
					return "Хв";
				if (second.Checked)
					return "Сек";
				return null;
			}
		}
	}
}
