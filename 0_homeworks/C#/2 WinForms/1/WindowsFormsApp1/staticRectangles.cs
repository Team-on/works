
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;

namespace WindowsFormsApp1 {
	public partial class staticRectangles : Form {
		Coord start, end;
		Graphics g;
		Pen p;
		Pen Invis;
		List<bool> printed;
		List<Rectangle> rectangle;
		System.Timers.Timer timer;
		int clicks;

		private void staticRectangle_MouseDown(object sender, MouseEventArgs e) {
			timer.Start();
			if (timer.Enabled)
				clicks = e.Clicks;

			start.x = e.X;
			start.y = e.Y;
		}

		private void staticRectangle_MouseUp(object sender, MouseEventArgs e) {
			end.x = e.X;
			end.y = e.Y;

			if (e.Button == MouseButtons.Left) {
				if (!timer.Enabled && (clicks == 0 || clicks == 1)) {
					AddRectangle();
				}
				if (timer.Enabled && clicks >= 2 && e.Button == MouseButtons.Left) {
					for (int i = 0; i < rectangle.Count; ++i) {
						if (rectangle[i].IsInside(new Coord(e.X, e.Y))) {
							if (printed[i]) {
								printed[i] = false;
								g.DrawRectangle(Invis, rectangle[i]);
								return;
							}
							else {

							}
						}
					}
				}
			}
		}

		void AddRectangle() {
			void swap(ref int a, ref int b) {
				var t = a;
				a = b;
				b = t;
			}
			if (start.x > end.x)
				swap(ref start.x, ref end.x);
			if (start.y > end.y)
				swap(ref start.y, ref end.y);

			if (end.x - start.x <= 10 && end.y - start.y <= 10 && MessageBox.Show("Size less than 10x10. Do u want to create it?", "Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) != DialogResult.Yes)
				return;
			rectangle.Add(new Rectangle(start.x, start.y, end.x - start.x, end.y - start.y));
			printed.Add(true);
			for (int i = 0; i < rectangle.Count; ++i) {
				//if (rectangle[i].IsInside(new Coord(e.X, e.Y))) {
				if (printed[i]) {
					g.DrawRectangle(p, rectangle[i]);
				}
				else {
					g.DrawRectangle(Invis, rectangle[i]);
				}
			}
		}

		private void staticRectangle_MouseClick(object sender, MouseEventArgs e) {
			if (e.Button == MouseButtons.Right) {
				for (int i = rectangle.Count - 1; i >= 0; --i)
					if (printed[i] && rectangle[i].IsInside(new Coord(e.X, e.Y))) {
						PrintRectInfo(rectangle[i]);
						return;
					}
			}

			void PrintRectInfo(Rectangle rect) {
				string text = "";
				text += "Area: " + (rect.Height * rect.Width).ToString();
				text += '\n';
				text += "Coord: " + string.Format($"x->{rect.X}, y->{rect.Y}");
				text += '\n';
				text += "Size: " + string.Format($"x->{rect.Width}, y->{rect.Height}");
				MessageBox.Show(text, "RectInfo", MessageBoxButtons.OK, MessageBoxIcon.Information);
			}
		}

		private void staticRectangle_MouseDoubleClick(object sender, MouseEventArgs e) {

		}

		public staticRectangles() {
			InitializeComponent();
			g = CreateGraphics();
			p = new Pen(Color.DarkOrange, 6);
			Invis = new Pen(this.BackColor, p.Width);
			rectangle = new List<Rectangle>();
			printed = new List<bool>();
			timer = new System.Timers.Timer();
			timer.Elapsed += new ElapsedEventHandler(timer_Elapsed);
			timer.Interval = 300;
			timer.AutoReset = false;
		}

		public void timer_Elapsed(Object source, ElapsedEventArgs e) {
			timer.Stop();
			//MessageBox.Show(clicks.ToString());
			clicks = 0;
		}
	}

	struct Coord {
		public int x, y;
		public Coord(int X, int Y) {
			x = X;
			y = Y;
		}

		public void Deconstruct(out int x, out int y) {
			x = this.x;
			y = this.y;
		}
	}

	static partial class Extensions {
		public static bool IsInside(this Rectangle rectangle, Coord c) {
			if (rectangle.X <= c.x && c.x <= rectangle.Right && rectangle.Y <= c.y && c.y <= rectangle.Bottom)
				return true;
			return false;
		}
	}
}