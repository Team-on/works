namespace CodeStudio {
	partial class FileCreator {
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
			this.treeView1 = new System.Windows.Forms.TreeView();
			this.listView1 = new System.Windows.Forms.ListView();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// treeView1
			// 
			this.treeView1.Location = new System.Drawing.Point(12, 12);
			this.treeView1.Name = "treeView1";
			this.treeView1.Size = new System.Drawing.Size(267, 449);
			this.treeView1.TabIndex = 0;
			// 
			// listView1
			// 
			this.listView1.Location = new System.Drawing.Point(300, 13);
			this.listView1.Name = "listView1";
			this.listView1.Size = new System.Drawing.Size(320, 448);
			this.listView1.TabIndex = 1;
			this.listView1.UseCompatibleStateImageBehavior = false;
			// 
			// textBox1
			// 
			this.textBox1.Enabled = false;
			this.textBox1.Location = new System.Drawing.Point(640, 12);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(233, 449);
			this.textBox1.TabIndex = 2;
			// 
			// FileCreator
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(885, 473);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.listView1);
			this.Controls.Add(this.treeView1);
			this.Name = "FileCreator";
			this.Text = "FileCreator";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TreeView treeView1;
		private System.Windows.Forms.ListView listView1;
		private System.Windows.Forms.TextBox textBox1;
	}
}