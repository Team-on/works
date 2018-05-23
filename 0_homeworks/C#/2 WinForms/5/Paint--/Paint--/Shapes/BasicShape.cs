using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using static Paint__.Singletones;

namespace Paint__.Shapes {
	abstract class BasicShape {
		//-------------------- Prop -----------------------------------
		public Point Start => start;

		public Pen Border => border;
		public Brush Fill => fill;

		public Brush TextBrush => textBrush;
		public Font TextFont => textFont;
		public string Text => text;

		//-------------------- Metods -----------------------------------
		abstract public void Draw(Graphics graphics);

		//-------------------- Fields -----------------------------------
		protected Point start;

		protected Pen border;
		protected Brush fill;

		protected Brush textBrush;
		protected Font textFont;
		protected string text;
	}
}
