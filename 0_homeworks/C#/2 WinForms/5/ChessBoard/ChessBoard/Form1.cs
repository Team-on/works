using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChessBoard {
	public partial class Form1 : Form {
		public Form1() {
			InitializeComponent();

			this.Resize += (s, args) => DrawChessBoard((s as Form).CreateGraphics(),
				10,
				(((s as Form).ClientRectangle.Height < (s as Form).ClientRectangle.Width) ?
				(s as Form).ClientRectangle.Height :
				(s as Form).ClientRectangle.Width) / 10,
				true
				);

			this.Paint += (s, args) => DrawChessBoard((s as Form).CreateGraphics(),
				10,
				(((s as Form).ClientRectangle.Height < (s as Form).ClientRectangle.Width) ?
				(s as Form).ClientRectangle.Height :
				(s as Form).ClientRectangle.Width) / 10,
				false
				);
		}

		public void DrawChessBoard(Graphics graphics, int start, int size, bool needClear) {
			Rectangle rectangle;
			Pen border = new Pen(Color.Orange, 3);
			Brush fill1 = new SolidBrush(Color.Black), fill2 = new SolidBrush(Color.White);

			Font font = new Font(FontFamily.GenericSansSerif, size / 2 + 1, FontStyle.Bold | FontStyle.Italic);
			Brush textBrush = new SolidBrush(Color.SteelBlue);
			int ocroSize = (size << 3) + start, size2;

			if (needClear)
				graphics.Clear(Color.FromKnownColor(KnownColor.ActiveBorder));

			ushort[] SizesArr = new ushort[8] { (ushort)start, (ushort)(start + 1 * size), (ushort)(start + (size << 1)), (ushort)(start + 3 * size), (ushort)(start + (size<<2)), (ushort)(start + 5 * size), (ushort)(start + 6 * size), (ushort)(start + 7 * size) };

			//graphics.FillRectangle(fill2, start, start, size << 3, size << 3);

			for (byte i = 0; i < 8; ++i) {
				for (byte j = 0; j < 8; ++j) {
					rectangle = new Rectangle(SizesArr[i], SizesArr[j], size, size);
					graphics.FillRectangle(((i & 1) == (j & 1))? fill2 : fill1, rectangle);
					//graphics.FillRectangle((((i ^ j) & 1) == 0) ? fill2 : fill1, rectangle);

					//if ((i & 1) != (j & 1))
					//	graphics.FillRectangle(fill1, rectangle);
					graphics.DrawRectangle(border, rectangle);
				}

				size2 = start + i * size + (size >> 2);
				graphics.DrawString(((char)('a' + i)).ToString(), font, textBrush, new Point(size2, ocroSize));
				graphics.DrawString(i.ToString(), font, textBrush, new Point(ocroSize, size2));
			}

			System.Threading.Thread.Sleep(5);
		}
	}
}
