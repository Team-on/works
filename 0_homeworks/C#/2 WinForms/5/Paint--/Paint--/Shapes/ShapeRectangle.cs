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
	class ShapeRectangle : BasicShape {
		//-------------------- Prop -----------------------------------
		Size Size => size;

		//-------------------- Metods -----------------------------------
		override public void Draw(Graphics graphics) {
			if(Fill != null)
				graphics.FillRectangle(Fill, Start.X, Start.Y, Size.Width, Size.Height);
			if (Border != null)
				graphics.DrawRectangle(Border, Start.X, Start.Y, Size.Width, Size.Height);
			if (Text != null)
				graphics.DrawRectangle(Border, Start.X, Start.Y, Size.Width, Size.Height);
		}

		//-------------------- Fields -----------------------------------
		protected Size size;
	}
}
