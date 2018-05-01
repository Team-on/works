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
					return string.Format("{0:0.##}",GetMnthCnt(DateTime.Now, date.Value)); 
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
				double mnt = 0, avgDay = 0;
				DateTime i = start;
				int prevMnt = i.Month, days = 0, allDays = 0;

				for (; i < end; i = i.AddDays(1)) {
					if (prevMnt != i.Month) {
						prevMnt = i.Month;
						++mnt;
						if (avgDay == 0)
							avgDay = i.AddDays(-1).Day;
						else
							avgDay = (avgDay + i.AddDays(-1).Day) / 2;
						days = 0;
					}
					++days;
					++allDays;
				}

				if(avgDay != 0)
					return allDays / avgDay;
				return allDays * 1.0 / GetMntDay(end.Month);

				double GetMntDay(int m) {
					double res = 31;
					if (m == 2)
						res = 28;
					else if (m == 4 || m == 6 || m == 9 || m == 11)
						res = 30;
					return res;
				}
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
