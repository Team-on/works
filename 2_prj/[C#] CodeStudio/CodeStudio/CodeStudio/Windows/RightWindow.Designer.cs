namespace CodeStudio {
	partial class RightWindow {
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
			this.tabPageExplorer = new System.Windows.Forms.TabPage();
			this.tabPageProperties = new System.Windows.Forms.TabPage();
			this.Explorer = new System.Windows.Forms.TreeView();
			this.tabControl1.SuspendLayout();
			this.tabPageExplorer.SuspendLayout();
			this.SuspendLayout();
			// 
			// tabControl1
			// 
			this.tabControl1.Alignment = System.Windows.Forms.TabAlignment.Bottom;
			this.tabControl1.Controls.Add(this.tabPageExplorer);
			this.tabControl1.Controls.Add(this.tabPageProperties);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Multiline = true;
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(292, 273);
			this.tabControl1.TabIndex = 1;
			// 
			// tabPageExplorer
			// 
			this.tabPageExplorer.Controls.Add(this.Explorer);
			this.tabPageExplorer.Location = new System.Drawing.Point(4, 4);
			this.tabPageExplorer.Name = "tabPageExplorer";
			this.tabPageExplorer.Padding = new System.Windows.Forms.Padding(3);
			this.tabPageExplorer.Size = new System.Drawing.Size(284, 247);
			this.tabPageExplorer.TabIndex = 0;
			this.tabPageExplorer.Text = "Explorer";
			this.tabPageExplorer.UseVisualStyleBackColor = true;
			// 
			// tabPageProperties
			// 
			this.tabPageProperties.Location = new System.Drawing.Point(4, 4);
			this.tabPageProperties.Name = "tabPageProperties";
			this.tabPageProperties.Size = new System.Drawing.Size(284, 247);
			this.tabPageProperties.TabIndex = 1;
			this.tabPageProperties.Text = "Properties";
			this.tabPageProperties.UseVisualStyleBackColor = true;
			// 
			// Explorer
			// 
			this.Explorer.Dock = System.Windows.Forms.DockStyle.Fill;
			this.Explorer.Location = new System.Drawing.Point(3, 3);
			this.Explorer.Name = "Explorer";
			this.Explorer.Size = new System.Drawing.Size(278, 241);
			this.Explorer.TabIndex = 0;
			// 
			// RightWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292, 273);
			this.Controls.Add(this.tabControl1);
			this.Name = "RightWindow";
			this.Text = "RightWindow";
			this.tabControl1.ResumeLayout(false);
			this.tabPageExplorer.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion
		public System.Windows.Forms.TreeView Explorer;
		public System.Windows.Forms.TabPage tabPageExplorer;
		public System.Windows.Forms.TabControl tabControl1;
		public System.Windows.Forms.TabPage tabPageProperties;
	}
}