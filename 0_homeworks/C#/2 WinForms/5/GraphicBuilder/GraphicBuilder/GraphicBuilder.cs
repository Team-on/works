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
	public class GraphicBuilder {
		public Brush textBrush = new SolidBrush(Color.Black);
		public Font textFont = new Font(FontFamily.GenericSansSerif, 14);

		public Brush pointTextBrush = new SolidBrush(Color.Black);
		public Font pointTextFont = new Font(FontFamily.GenericSansSerif, 9);

		public Pen graphicLine = new Pen(Color.Blue);

		List<Point> points = new List<Point>(8);
		string textHorisontal, textVertical;

		/// <summary>
		/// Встановює массив точок, які будуть виведені методом Draw()
		/// </summary>
		/// <param name="Points">Точки. Зєднуватися будуть по типу point[i] point[i + 1]</param>
		public void SetValues(List<Point> Points) => points = Points;

		/// <summary>
		/// Встановює підписи
		/// </summary>
		public void SetText(string horisontal, string vertical) {
			textHorisontal = horisontal;
			textVertical = vertical;
		}

		/// <summary>
		/// Вивід графіку на формі. Розмір буде динамічним
		/// </summary>
		public void Draw(Form form) {
			Graphics graphics = form.CreateGraphics();
			Point size, startPos;
			startPos = new Point(10, 10);
			size = new Point(form.ClientRectangle.Width - startPos.X - 40, form.ClientRectangle.Height - startPos.Y - 40);
			if (size.X < 0 || size.Y < 0)
				return;

			Point onePersentSize = new Point((size.X) / 100, (size.Y) / 100);

			Point max = new Point {
				X = points[points.Count - 1].X
			};
			foreach (var i in points)
				if (i.Y > max.Y)
					max.Y = i.Y;

			DrawBackground();
			DrawText();
			DrawPoints();


			void DrawPoints() {
				float onePersentX = ((float)(max.X)) / 100;
				float onePersentY = ((float)(max.Y)) / 100;

				int i = 0;

				int currXPersent = (int)(points[i].X / onePersentX),
					currYPersent = (int)(points[i].Y / onePersentY),
					prevXPersent = (int)(points[i].X / onePersentX), 
					prevYPersent = (int)(points[i].Y / onePersentY);

				graphics.DrawString($"{points[i].X}, {points[i].Y}", pointTextFont, pointTextBrush,
						currXPersent * onePersentSize.X + startPos.X,
						(100 - currYPersent) * onePersentSize.Y + startPos.Y
					);

				++i;
				for (; i < points.Count; ++i) {
					currXPersent = (int)(points[i].X / onePersentX);
					currYPersent = (int)(points[i].Y / onePersentY);

					graphics.DrawLine(graphicLine,
						prevXPersent * onePersentSize.X + startPos.X + 30, 
						(100 - prevYPersent) * onePersentSize.Y + startPos.Y + 10, 
						currXPersent * onePersentSize.X + startPos.X + 30, 
						(100 - currYPersent) * onePersentSize.Y + startPos.Y + 10
					);

					graphics.DrawString($"{points[i].X}, {points[i].Y}", pointTextFont, pointTextBrush,
						currXPersent * onePersentSize.X + startPos.X ,
						(100 - currYPersent) * onePersentSize.Y + startPos.Y
					);

					prevYPersent = currYPersent;
					prevXPersent = currXPersent;
				}
			}

			void DrawBackground() {
				graphics.FillRectangle(new SolidBrush(Color.White), startPos.X, startPos.Y, size.X, size.Y);

			}

			void DrawText() {
				graphics.DrawString(textHorisontal, textFont, textBrush, new Point(startPos.X + size.X / 2 - ((int)(textHorisontal.Length * textFont.Size / 2)), startPos.Y + size.Y - 25));

				for (int i = 0; i < textVertical.Length; ++i) {
					graphics.DrawString(textVertical[i].ToString(), textFont, textBrush, new Point(startPos.X + 0, startPos.Y +
						((int)(size.Y / 2 - textVertical.Length * textFont.Size / 2)) +
						((int)(textFont.Size + 5)) * i));
				}
			}
		}
	}
}
