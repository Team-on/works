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
			this.listView = new System.Windows.Forms.ListView();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.button1 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// treeView1
			// 
			this.treeView1.Location = new System.Drawing.Point(12, 12);
			this.treeView1.Name = "treeView1";
			this.treeView1.Size = new System.Drawing.Size(267, 381);
			this.treeView1.TabIndex = 0;
			// 
			// listView
			// 
			this.listView.Location = new System.Drawing.Point(300, 13);
			this.listView.MultiSelect = false;
			this.listView.Name = "listView";
			this.listView.Size = new System.Drawing.Size(320, 380);
			this.listView.TabIndex = 1;
			this.listView.UseCompatibleStateImageBehavior = false;
			this.listView.View = System.Windows.Forms.View.List;
			this.listView.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listView_MouseDoubleClick);
			// 
			// textBox1
			// 
			this.textBox1.Enabled = false;
			this.textBox1.Location = new System.Drawing.Point(640, 12);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(233, 381);
			this.textBox1.TabIndex = 2;
			// 
			// button1
			// 
			this.button1.Font = new System.Drawing.Font("Comic Sans MS", 30F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.button1.Location = new System.Drawing.Point(640, 399);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(233, 62);
			this.button1.TabIndex = 3;
			this.button1.Text = "Ok";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// FileCreator
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(885, 473);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.textBox1);
			this.Controls.Add(this.listView);
			this.Controls.Add(this.treeView1);
			this.Name = "FileCreator";
			this.Text = "FileCreator";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TreeView treeView1;
		private System.Windows.Forms.ListView listView;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button button1;
	}
}