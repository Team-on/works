namespace FileLocker {
	partial class LockListWindow {
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
			this.menuStrip = new System.Windows.Forms.MenuStrip();
			this.statusStrip = new System.Windows.Forms.StatusStrip();
			this.groupBox = new System.Windows.Forms.GroupBox();
			this.buttonLock = new System.Windows.Forms.Button();
			this.buttonMore = new System.Windows.Forms.Button();
			this.textBox = new System.Windows.Forms.TextBox();
			this.listBox = new System.Windows.Forms.ListBox();
			this.groupBox.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip
			// 
			this.menuStrip.Location = new System.Drawing.Point(0, 0);
			this.menuStrip.Name = "menuStrip";
			this.menuStrip.Size = new System.Drawing.Size(389, 24);
			this.menuStrip.TabIndex = 2;
			this.menuStrip.Text = "menuStrip1";
			// 
			// statusStrip
			// 
			this.statusStrip.Location = new System.Drawing.Point(0, 292);
			this.statusStrip.Name = "statusStrip";
			this.statusStrip.Size = new System.Drawing.Size(389, 22);
			this.statusStrip.TabIndex = 3;
			this.statusStrip.Text = "statusStrip1";
			// 
			// groupBox
			// 
			this.groupBox.Controls.Add(this.buttonLock);
			this.groupBox.Controls.Add(this.buttonMore);
			this.groupBox.Controls.Add(this.textBox);
			this.groupBox.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.groupBox.Location = new System.Drawing.Point(0, 238);
			this.groupBox.Name = "groupBox";
			this.groupBox.Size = new System.Drawing.Size(389, 54);
			this.groupBox.TabIndex = 4;
			this.groupBox.TabStop = false;
			// 
			// buttonLock
			// 
			this.buttonLock.Location = new System.Drawing.Point(311, 20);
			this.buttonLock.Name = "buttonLock";
			this.buttonLock.Size = new System.Drawing.Size(67, 22);
			this.buttonLock.TabIndex = 2;
			this.buttonLock.Text = "Lock";
			this.buttonLock.UseVisualStyleBackColor = true;
			this.buttonLock.Click += new System.EventHandler(this.buttonLock_Click);
			// 
			// buttonMore
			// 
			this.buttonMore.Font = new System.Drawing.Font("Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.buttonMore.Location = new System.Drawing.Point(280, 20);
			this.buttonMore.Name = "buttonMore";
			this.buttonMore.Size = new System.Drawing.Size(21, 23);
			this.buttonMore.TabIndex = 1;
			this.buttonMore.Text = "...";
			this.buttonMore.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.buttonMore.UseVisualStyleBackColor = true;
			this.buttonMore.Click += new System.EventHandler(this.buttonMore_Click);
			// 
			// textBox
			// 
			this.textBox.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
			this.textBox.Location = new System.Drawing.Point(7, 20);
			this.textBox.Name = "textBox";
			this.textBox.Size = new System.Drawing.Size(273, 20);
			this.textBox.TabIndex = 0;
			this.textBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox_KeyDown);
			// 
			// listBox
			// 
			this.listBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.listBox.FormattingEnabled = true;
			this.listBox.Location = new System.Drawing.Point(0, 24);
			this.listBox.Name = "listBox";
			this.listBox.Size = new System.Drawing.Size(389, 214);
			this.listBox.TabIndex = 5;
			// 
			// LockListWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(389, 314);
			this.Controls.Add(this.listBox);
			this.Controls.Add(this.groupBox);
			this.Controls.Add(this.statusStrip);
			this.Controls.Add(this.menuStrip);
			this.MainMenuStrip = this.menuStrip;
			this.Name = "LockListWindow";
			this.Text = "LockListWindow";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.LockListWindow_FormClosing);
			this.groupBox.ResumeLayout(false);
			this.groupBox.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip;
		private System.Windows.Forms.StatusStrip statusStrip;
		private System.Windows.Forms.GroupBox groupBox;
		private System.Windows.Forms.Button buttonLock;
		private System.Windows.Forms.Button buttonMore;
		private System.Windows.Forms.TextBox textBox;
		private System.Windows.Forms.ListBox listBox;
	}
}