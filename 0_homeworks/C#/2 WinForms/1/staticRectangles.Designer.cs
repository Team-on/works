﻿namespace WindowsFormsApp1 {
	partial class staticRectangles {
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
			this.SuspendLayout();
			// 
			// staticRectangles
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(597, 337);
			this.Name = "staticRectangles";
			this.Text = "staticRectangles";
			this.MouseClick += new System.Windows.Forms.MouseEventHandler(this.staticRectangle_MouseClick);
			this.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.staticRectangle_MouseDoubleClick);
			this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.staticRectangle_MouseDown);
			this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.staticRectangle_MouseUp);
			this.ResumeLayout(false);

		}

		#endregion
	}
}