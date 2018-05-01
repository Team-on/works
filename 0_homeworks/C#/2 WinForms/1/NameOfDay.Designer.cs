namespace WindowsFormsApp1 {
	partial class NameOfDay {
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
			this.date = new System.Windows.Forms.MonthCalendar();
			this.day = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// date
			// 
			this.date.Location = new System.Drawing.Point(18, 18);
			this.date.MaxSelectionCount = 1;
			this.date.Name = "date";
			this.date.TabIndex = 0;
			this.date.DateChanged += new System.Windows.Forms.DateRangeEventHandler(this.monthCalendar1_DateChanged);
			// 
			// day
			// 
			this.day.AutoSize = true;
			this.day.Font = new System.Drawing.Font("Comic Sans MS", 25F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.day.Location = new System.Drawing.Point(10, 200);
			this.day.Name = "day";
			this.day.Size = new System.Drawing.Size(189, 47);
			this.day.TabIndex = 1;
			this.day.Text = "Select day";
			// 
			// NameOfDay
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(411, 271);
			this.Controls.Add(this.day);
			this.Controls.Add(this.date);
			this.Name = "NameOfDay";
			this.Text = "NameOfDay";
			this.Load += new System.EventHandler(this.NameOfDay_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MonthCalendar date;
		private System.Windows.Forms.Label day;
	}
}