﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CodeStudio {
	public partial class LeftWindow : Form {
		public LeftWindow() {
			InitializeComponent();
		}

		private void LeftWindow_Shown(object sender, EventArgs e) {
			tabPageToolBox.ForeColor = Singletones.settings.DefaultForeground;
			tabPageToolBox.BackColor = Singletones.settings.DefaultBackground;
			this.ForeColor = Singletones.settings.DefaultForeground;
			this.BackColor = Singletones.settings.DefaultBackground;

			this.FormBorderStyle = FormBorderStyle.SizableToolWindow;
		}
	}
}
