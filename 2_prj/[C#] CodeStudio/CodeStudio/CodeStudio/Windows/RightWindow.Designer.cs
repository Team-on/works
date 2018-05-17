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
			this.components = new System.ComponentModel.Container();
			this.tabControl1 = new System.Windows.Forms.TabControl();
			this.tabPageExplorer = new System.Windows.Forms.TabPage();
			this.Explorer = new System.Windows.Forms.TreeView();
			this.tabPageProperties = new System.Windows.Forms.TabPage();
			this.explorerContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
			this.tabControl1.SuspendLayout();
			this.tabPageExplorer.SuspendLayout();
			this.explorerContextMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// tabControl1
			// 
			this.tabControl1.Alignment = System.Windows.Forms.TabAlignment.Bottom;
			this.tabControl1.Controls.Add(this.tabPageExplorer);
			this.tabControl1.Controls.Add(this.tabPageProperties);
			this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.tabControl1.Location = new System.Drawing.Point(0, 0);
			this.tabControl1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabControl1.Multiline = true;
			this.tabControl1.Name = "tabControl1";
			this.tabControl1.SelectedIndex = 0;
			this.tabControl1.Size = new System.Drawing.Size(341, 336);
			this.tabControl1.TabIndex = 1;
			// 
			// tabPageExplorer
			// 
			this.tabPageExplorer.Controls.Add(this.Explorer);
			this.tabPageExplorer.Location = new System.Drawing.Point(4, 4);
			this.tabPageExplorer.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageExplorer.Name = "tabPageExplorer";
			this.tabPageExplorer.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageExplorer.Size = new System.Drawing.Size(333, 307);
			this.tabPageExplorer.TabIndex = 0;
			this.tabPageExplorer.Text = "Explorer";
			this.tabPageExplorer.UseVisualStyleBackColor = true;
			// 
			// Explorer
			// 
			this.Explorer.Dock = System.Windows.Forms.DockStyle.Fill;
			this.Explorer.Location = new System.Drawing.Point(3, 4);
			this.Explorer.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.Explorer.Name = "Explorer";
			this.Explorer.Size = new System.Drawing.Size(327, 299);
			this.Explorer.TabIndex = 0;
			this.Explorer.DoubleClick += new System.EventHandler(this.Explorer_DoubleClick);
			this.Explorer.MouseClick += new System.Windows.Forms.MouseEventHandler(this.Explorer_MouseClick);
			// 
			// tabPageProperties
			// 
			this.tabPageProperties.Location = new System.Drawing.Point(4, 4);
			this.tabPageProperties.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.tabPageProperties.Name = "tabPageProperties";
			this.tabPageProperties.Size = new System.Drawing.Size(333, 307);
			this.tabPageProperties.TabIndex = 1;
			this.tabPageProperties.Text = "Properties";
			this.tabPageProperties.UseVisualStyleBackColor = true;
			// 
			// explorerContextMenu
			// 
			this.explorerContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.toolStripMenuItem2});
			this.explorerContextMenu.Name = "contextMenuStrip1";
			this.explorerContextMenu.Size = new System.Drawing.Size(101, 48);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(100, 22);
			this.toolStripMenuItem1.Text = "Open";
			this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
			// 
			// toolStripMenuItem2
			// 
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new System.Drawing.Size(100, 22);
			this.toolStripMenuItem2.Text = "Close";
			this.toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem2_Click);
			// 
			// RightWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(341, 336);
			this.Controls.Add(this.tabControl1);
			this.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
			this.Name = "RightWindow";
			this.Text = "RightWindow";
			this.Shown += new System.EventHandler(this.RightWindow_Shown);
			this.tabControl1.ResumeLayout(false);
			this.tabPageExplorer.ResumeLayout(false);
			this.explorerContextMenu.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion
		public System.Windows.Forms.TreeView Explorer;
		public System.Windows.Forms.TabPage tabPageExplorer;
		public System.Windows.Forms.TabControl tabControl1;
		public System.Windows.Forms.TabPage tabPageProperties;
		private System.Windows.Forms.ContextMenuStrip explorerContextMenu;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
	}
}