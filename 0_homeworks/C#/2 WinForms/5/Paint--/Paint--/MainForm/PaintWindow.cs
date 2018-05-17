using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static Paint__.Singletones;

namespace Paint__ {
	public partial class PaintWindow : Form {
		public static DisplayWindow displayWindow = new DisplayWindow();

		public PaintWindow() {
			InitializeComponent();

			displayWindow.MdiParent = this;
			displayWindow.Dock = DockStyle.Fill;
			mainWindow = this;
		}

		private void PaintWindow_Shown(object sender, EventArgs e) {
			displayWindow.Show();

			palitreColor.Show();
			palitrePickFigure.Show();
			figureLayers.Show();

			figureLayers.Location = new Point(mainWindow.Width - figureLayers.Width - 10, mainWindow.Height - figureLayers.Height - 10);

			palitreColor.Location = new Point(mainWindow.Width - palitreColor.Width - 10, mainWindow.ClientRectangle.Y + 22);

			palitrePickFigure.Location = new Point(mainWindow.ClientRectangle.X + 2, mainWindow.ClientRectangle.Y + 22);

		}

		private void PaintWindow_Click(object sender, EventArgs e) {

		}
	}
}
