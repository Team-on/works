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
			this.groupBox = new System.Windows.Forms.GroupBox();
			this.buttonLock = new System.Windows.Forms.Button();
			this.buttonMore = new System.Windows.Forms.Button();
			this.textBox = new System.Windows.Forms.TextBox();
			this.listBox = new System.Windows.Forms.ListBox();
			this.buttonRemove = new System.Windows.Forms.Button();
			this.buttonUnlock = new System.Windows.Forms.Button();
			this.buttonLockback = new System.Windows.Forms.Button();
			this.buttonLockAll = new System.Windows.Forms.Button();
			this.buttonUnlockAll = new System.Windows.Forms.Button();
			this.groupBox.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox
			// 
			this.groupBox.Controls.Add(this.buttonUnlockAll);
			this.groupBox.Controls.Add(this.buttonLockAll);
			this.groupBox.Controls.Add(this.buttonUnlock);
			this.groupBox.Controls.Add(this.buttonLockback);
			this.groupBox.Controls.Add(this.buttonRemove);
			this.groupBox.Controls.Add(this.buttonLock);
			this.groupBox.Controls.Add(this.buttonMore);
			this.groupBox.Controls.Add(this.textBox);
			this.groupBox.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.groupBox.Location = new System.Drawing.Point(0, 222);
			this.groupBox.Name = "groupBox";
			this.groupBox.Size = new System.Drawing.Size(389, 92);
			this.groupBox.TabIndex = 4;
			this.groupBox.TabStop = false;
			// 
			// buttonLock
			// 
			this.buttonLock.Location = new System.Drawing.Point(310, 60);
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
			this.buttonMore.Location = new System.Drawing.Point(279, 60);
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
			this.textBox.Location = new System.Drawing.Point(6, 60);
			this.textBox.Name = "textBox";
			this.textBox.Size = new System.Drawing.Size(273, 20);
			this.textBox.TabIndex = 0;
			this.textBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBox_KeyDown);
			// 
			// listBox
			// 
			this.listBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.listBox.FormattingEnabled = true;
			this.listBox.Location = new System.Drawing.Point(0, 0);
			this.listBox.Name = "listBox";
			this.listBox.Size = new System.Drawing.Size(389, 222);
			this.listBox.TabIndex = 5;
			// 
			// buttonRemove
			// 
			this.buttonRemove.Location = new System.Drawing.Point(310, 19);
			this.buttonRemove.Name = "buttonRemove";
			this.buttonRemove.Size = new System.Drawing.Size(67, 22);
			this.buttonRemove.TabIndex = 2;
			this.buttonRemove.Text = "Remove";
			this.buttonRemove.UseVisualStyleBackColor = true;
			this.buttonRemove.Click += new System.EventHandler(this.buttonRemove_Click);
			// 
			// buttonUnlock
			// 
			this.buttonUnlock.Location = new System.Drawing.Point(233, 19);
			this.buttonUnlock.Name = "buttonUnlock";
			this.buttonUnlock.Size = new System.Drawing.Size(67, 22);
			this.buttonUnlock.TabIndex = 2;
			this.buttonUnlock.Text = "Unlock";
			this.buttonUnlock.UseVisualStyleBackColor = true;
			this.buttonUnlock.Click += new System.EventHandler(this.buttonUnlock_Click);
			// 
			// buttonLockback
			// 
			this.buttonLockback.Location = new System.Drawing.Point(160, 19);
			this.buttonLockback.Name = "buttonLockback";
			this.buttonLockback.Size = new System.Drawing.Size(67, 22);
			this.buttonLockback.TabIndex = 2;
			this.buttonLockback.Text = "Lockback";
			this.buttonLockback.UseVisualStyleBackColor = true;
			this.buttonLockback.Click += new System.EventHandler(this.buttonLockback_Click);
			// 
			// buttonLockAll
			// 
			this.buttonLockAll.Location = new System.Drawing.Point(14, 19);
			this.buttonLockAll.Name = "buttonLockAll";
			this.buttonLockAll.Size = new System.Drawing.Size(67, 22);
			this.buttonLockAll.TabIndex = 2;
			this.buttonLockAll.Text = "Lock all";
			this.buttonLockAll.UseVisualStyleBackColor = true;
			this.buttonLockAll.Click += new System.EventHandler(this.buttonLockAll_Click);
			// 
			// buttonUnlockAll
			// 
			this.buttonUnlockAll.Location = new System.Drawing.Point(87, 19);
			this.buttonUnlockAll.Name = "buttonUnlockAll";
			this.buttonUnlockAll.Size = new System.Drawing.Size(67, 22);
			this.buttonUnlockAll.TabIndex = 2;
			this.buttonUnlockAll.Text = "Unlock all";
			this.buttonUnlockAll.UseVisualStyleBackColor = true;
			this.buttonUnlockAll.Click += new System.EventHandler(this.buttonUnlockAll_Click);
			// 
			// LockListWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(389, 314);
			this.Controls.Add(this.listBox);
			this.Controls.Add(this.groupBox);
			this.Name = "LockListWindow";
			this.Text = "LockListWindow";
			this.Activated += new System.EventHandler(this.LockListWindow_Activated);
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.LockListWindow_FormClosing);
			this.groupBox.ResumeLayout(false);
			this.groupBox.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion
		private System.Windows.Forms.GroupBox groupBox;
		private System.Windows.Forms.Button buttonLock;
		private System.Windows.Forms.Button buttonMore;
		private System.Windows.Forms.TextBox textBox;
		private System.Windows.Forms.ListBox listBox;
		private System.Windows.Forms.Button buttonUnlock;
		private System.Windows.Forms.Button buttonLockback;
		private System.Windows.Forms.Button buttonRemove;
		private System.Windows.Forms.Button buttonUnlockAll;
		private System.Windows.Forms.Button buttonLockAll;
	}
}