namespace CodeStudio {
	partial class LeftWindow {
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
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabPageToolBox = new System.Windows.Forms.TabPage();
			this.tabControl1.SuspendLayout();
			this.SuspendLayout();
			// 
			// tabControl1
			// 
			this.tabControl1.Alignment = System.Windows.Forms.TabAlignment.Bottom;
			this.tabControl1.Controls.Add(this.tabPageToolBox);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(423, 350);
			this.tabControl1.TabIndex = 1;
			// 
			// tabPageToolBox
			// 
			this.tabPageToolBox.Location = new System.Drawing.Point(4, 4);
			this.tabPageToolBox.Name = "tabPageToolBox";
			this.tabPageToolBox.Size = new System.Drawing.Size(415, 324);
			this.tabPageToolBox.TabIndex = 0;
			this.tabPageToolBox.Text = "toolBox";
			this.tabPageToolBox.UseVisualStyleBackColor = true;
			// 
			// LeftWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(423, 350);
			this.Controls.Add(this.tabControl1);
			this.Name = "LeftWindow";
			this.Text = "LeftWindow";
			this.Shown += new System.EventHandler(this.LeftWindow_Shown);
			this.tabControl1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPageToolBox;
	}
}