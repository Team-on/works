using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CodeStudio {
	public partial class CodeStudioMain : Form {
		CodeWindow codeWindow;
		DownWindow downWindow;
		LeftWindow leftWindow;
		RightWindow rightWindow;


		public CodeStudioMain() {
			InitializeComponent();
			codeWindow = new CodeWindow {
				MdiParent = this,
				FormBorderStyle = FormBorderStyle.None
			};
			downWindow = new DownWindow { MdiParent = this };
			leftWindow = new LeftWindow { MdiParent = this };
			rightWindow = new RightWindow { MdiParent = this };

			codeWindow.ResizeEnd += ResizeFields;
			downWindow.ResizeEnd += ResizeFields;
			leftWindow.ResizeEnd += ResizeFields;
			rightWindow.ResizeEnd += ResizeFields;
		}


		private void CodeStudioMain_Shown(object sender, EventArgs e) {
			codeWindow.Show();
			downWindow.Show();
			leftWindow.Show();
			rightWindow.Show();

			Size size = this.ClientRectangle.Size;
			size.Height -= statusStrip.Height + menuStrip.Height + 4;
			size.Width -= 4;

			leftWindow.Size = new Size(size.Width / 5, size.Height);
			leftWindow.Location = new Point(0, 0);

			rightWindow.Size = new Size(size.Width / 5, size.Height);
			rightWindow.Location = new Point(size.Width - rightWindow.Size.Width, 0);

			downWindow.Size = new Size(size.Width - leftWindow.Width - rightWindow.Width,
				size.Height / 5);
			downWindow.Location = new Point(leftWindow.Size.Width, 
				size.Height - downWindow.Height);

			codeWindow.Size = new Size(downWindow.Size.Width, size.Height - downWindow.Height);
			codeWindow.Location = new Point(leftWindow.Size.Width, leftWindow.Location.Y);
		}

		void ResizeFields(object sender, EventArgs e) {

			Size size = this.ClientRectangle.Size;
			size.Height -= statusStrip.Height + menuStrip.Height + 4;
			size.Width -= 4;

			if(sender == downWindow)
				ResizeLeft();
			if (sender == downWindow)
				ResizeRight();
			if (sender == leftWindow || sender == rightWindow)
				ResizeDown();
			if (sender == leftWindow || sender == rightWindow || sender == downWindow)
				ResizeCenter();


			void ResizeLeft() {
				leftWindow.Size = new Size(size.Width - downWindow.Width - rightWindow.Width, size.Height);
				leftWindow.Location = new Point(0, 0);
			}
			void ResizeRight() {
				rightWindow.Size = new Size(size.Width - downWindow.Width - leftWindow.Width, size.Height);
				rightWindow.Location = new Point(size.Width - rightWindow.Size.Width, 0);
			}
			void ResizeDown() {
				downWindow.Size = new Size(size.Width - leftWindow.Width - rightWindow.Width, size.Height - codeWindow.Height);
				downWindow.Location = new Point(leftWindow.Size.Width, size.Height - downWindow.Height);
			}
			void ResizeCenter() {
				codeWindow.Size = new Size(downWindow.Size.Width, size.Height - downWindow.Height);
				codeWindow.Location = new Point(leftWindow.Size.Width, leftWindow.Location.Y);
			}
		}
	}
}
