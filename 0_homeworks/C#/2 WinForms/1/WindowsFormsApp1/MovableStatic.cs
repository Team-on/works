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
	public partial class MovableStatic : Form {
		Button btn;
		Random r = new Random();
		
		public MovableStatic() {
			InitializeComponent();
			btn = new Button() {
				Location = new Point(this.Width / 2, Height / 2),
				Size = new Size(100, 30),
				Text = "I am avoid u",
				BackColor = Color.FromArgb(r.Next(255), r.Next(255), r.Next(255)),
				ForeColor = Color.FromArgb(r.Next(0, 50), r.Next(0, 50), r.Next(0, 50))
			};

			Controls.Add(btn);
		}

		void Avoid(object sender, MouseEventArgs e) {
			int shift = 5;
			++shift;
			if ((new Rectangle(btn.Location.X - shift, btn.Location.Y - shift, btn.Width + shift * 2, btn.Height + shift * 2)).Contains(e.Location)) {
				--shift;
				Point loc = btn.Location;
				if (Math.Abs(btn.Left - e.Location.X) <= shift)
					loc.X += shift;
				else if (Math.Abs(e.Location.X - btn.Right) <= shift)
					loc.X -= shift;
				if (Math.Abs(btn.Top - e.Location.Y) <= shift)
					loc.Y += shift;
				else if (Math.Abs(e.Location.Y - btn.Bottom) <= shift)
					loc.Y -= shift;
				if (loc.X < 0 || loc.Y < 0 || loc.X + btn.Width > this.Width || loc.Y + btn.Height * 2 + shift > this.Height) {
						MoveToRandPos();
				}
				else {
					btn.Location = loc;
					if (btn.Bottom <= e.Location.Y && e.Location.Y <= btn.Top && 
						btn.Left <= e.Location.X && e.Location.X <= btn.Right) 
						MoveToRandPos();
					
				}
			}

			void MoveToRandPos() {
				Rectangle rec = new Rectangle(new Point(0, 0), new Size(this.Size.Width - btn.Width - shift, this.Size.Height - btn.Height - shift));
				do btn.Location = new Point(r.Next(0, Width), r.Next(0, Height)); while (!rec.Contains(btn.Location));
			}
		}
	}
}
