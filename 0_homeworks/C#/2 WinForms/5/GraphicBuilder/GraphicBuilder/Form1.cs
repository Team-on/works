using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GraphicBuilder {
	public partial class Form1 : Form {
		GraphicBuilder graphicBuilder = new GraphicBuilder();

		public Form1() {
			InitializeComponent();
			graphicBuilder.SetText("horisontal", "Vertical");
			graphicBuilder.SetValues(new List<Point>() {new Point(0, 0), new Point(1, 1), new Point(2, 2), new Point(3, 3), new Point(4, 6), new Point(5, 10), new Point(6, 15), new Point(7, 12), new Point(8, 4), new Point(16, 100) });
		}

		private void Form1_Paint(object sender, PaintEventArgs e) {
			this.CreateGraphics().Clear(Color.FromKnownColor(KnownColor.ActiveBorder));
			graphicBuilder.Draw(this);
		}

		private void Form1_ResizeEnd(object sender, EventArgs e) {
			this.Refresh();
		}
	}
}
