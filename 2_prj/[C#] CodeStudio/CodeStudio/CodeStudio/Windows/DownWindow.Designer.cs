namespace CodeStudio {
	partial class DownWindow {
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
			this.tabPageCompiler = new System.Windows.Forms.TabPage();
			this.CompilerOutput = new System.Windows.Forms.RichTextBox();
			this.tabControl1.SuspendLayout();
			this.tabPageCompiler.SuspendLayout();
			this.SuspendLayout();
			// 
			// tabControl1
			// 
			this.tabControl1.Alignment = System.Windows.Forms.TabAlignment.Bottom;
			this.tabControl1.Controls.Add(this.tabPageCompiler);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(292, 273);
			this.tabControl1.TabIndex = 1;
			// 
			// tabPageCompiler
			// 
			this.tabPageCompiler.Controls.Add(this.CompilerOutput);
			this.tabPageCompiler.Location = new System.Drawing.Point(4, 4);
			this.tabPageCompiler.Name = "tabPageCompiler";
			this.tabPageCompiler.Size = new System.Drawing.Size(284, 247);
			this.tabPageCompiler.TabIndex = 0;
			this.tabPageCompiler.Text = "Compiler output";
			this.tabPageCompiler.UseVisualStyleBackColor = true;
			// 
			// CompilerOutput
			// 
			this.CompilerOutput.Dock = System.Windows.Forms.DockStyle.Fill;
			this.CompilerOutput.Location = new System.Drawing.Point(0, 0);
			this.CompilerOutput.Name = "CompilerOutput";
			this.CompilerOutput.Size = new System.Drawing.Size(284, 247);
			this.CompilerOutput.TabIndex = 0;
			this.CompilerOutput.Text = "";
			this.CompilerOutput.TextChanged += new System.EventHandler(this.CompilerOutput_TextChanged);
			this.CompilerOutput.KeyDown += new System.Windows.Forms.KeyEventHandler(this.CompilerOutput_KeyUp);
			this.CompilerOutput.KeyUp += new System.Windows.Forms.KeyEventHandler(this.CompilerOutput_KeyUp);
			// 
			// DownWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292, 273);
			this.Controls.Add(this.tabControl1);
			this.Name = "DownWindow";
			this.Text = "DownWindow";
			this.Shown += new System.EventHandler(this.DownWindow_Shown);
			this.tabControl1.ResumeLayout(false);
			this.tabPageCompiler.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.TabControl tabControl1;
		private System.Windows.Forms.TabPage tabPageCompiler;
		public System.Windows.Forms.RichTextBox CompilerOutput;
	}
}