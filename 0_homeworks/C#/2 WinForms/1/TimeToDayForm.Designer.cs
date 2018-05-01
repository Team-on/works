namespace WindowsFormsApp1 {
	partial class TimeToDayForm {
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
			this.date = new System.Windows.Forms.DateTimePicker();
			this.staticLabel1 = new System.Windows.Forms.Label();
			this.remain = new System.Windows.Forms.Label();
			this.choose = new System.Windows.Forms.GroupBox();
			this.year = new System.Windows.Forms.RadioButton();
			this.week = new System.Windows.Forms.RadioButton();
			this.mounth = new System.Windows.Forms.RadioButton();
			this.minute = new System.Windows.Forms.RadioButton();
			this.day = new System.Windows.Forms.RadioButton();
			this.second = new System.Windows.Forms.RadioButton();
			this.choose.SuspendLayout();
			this.SuspendLayout();
			// 
			// date
			// 
			this.date.Location = new System.Drawing.Point(24, 22);
			this.date.Name = "date";
			this.date.Size = new System.Drawing.Size(141, 20);
			this.date.TabIndex = 0;
			this.date.ValueChanged += new System.EventHandler(this.RecalcTime);
			// 
			// staticLabel1
			// 
			this.staticLabel1.AutoSize = true;
			this.staticLabel1.Location = new System.Drawing.Point(12, 173);
			this.staticLabel1.Name = "staticLabel1";
			this.staticLabel1.Size = new System.Drawing.Size(73, 13);
			this.staticLabel1.TabIndex = 6;
			this.staticLabel1.Text = "Залишилося:";
			// 
			// remain
			// 
			this.remain.AutoSize = true;
			this.remain.Font = new System.Drawing.Font("Comic Sans MS", 24.75F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.remain.Location = new System.Drawing.Point(16, 186);
			this.remain.Name = "remain";
			this.remain.Size = new System.Drawing.Size(236, 46);
			this.remain.TabIndex = 5;
			this.remain.Text = "Виберіть дату";
			// 
			// choose
			// 
			this.choose.Controls.Add(this.second);
			this.choose.Controls.Add(this.day);
			this.choose.Controls.Add(this.mounth);
			this.choose.Controls.Add(this.minute);
			this.choose.Controls.Add(this.week);
			this.choose.Controls.Add(this.year);
			this.choose.Location = new System.Drawing.Point(24, 62);
			this.choose.Name = "choose";
			this.choose.Size = new System.Drawing.Size(195, 98);
			this.choose.TabIndex = 7;
			this.choose.TabStop = false;
			this.choose.Text = "Як відображати час?";
			// 
			// year
			// 
			this.year.AutoSize = true;
			this.year.Location = new System.Drawing.Point(17, 20);
			this.year.Name = "year";
			this.year.Size = new System.Drawing.Size(50, 17);
			this.year.TabIndex = 0;
			this.year.TabStop = true;
			this.year.Text = "Роки";
			this.year.UseVisualStyleBackColor = true;
			// 
			// week
			// 
			this.week.AutoSize = true;
			this.week.Location = new System.Drawing.Point(17, 44);
			this.week.Name = "week";
			this.week.Size = new System.Drawing.Size(54, 17);
			this.week.TabIndex = 1;
			this.week.TabStop = true;
			this.week.Text = "Тижні";
			this.week.UseVisualStyleBackColor = true;
			// 
			// mounth
			// 
			this.mounth.AutoSize = true;
			this.mounth.Location = new System.Drawing.Point(108, 20);
			this.mounth.Name = "mounth";
			this.mounth.Size = new System.Drawing.Size(56, 17);
			this.mounth.TabIndex = 3;
			this.mounth.TabStop = true;
			this.mounth.Text = "Місяці";
			this.mounth.UseVisualStyleBackColor = true;
			// 
			// minute
			// 
			this.minute.AutoSize = true;
			this.minute.Location = new System.Drawing.Point(17, 67);
			this.minute.Name = "minute";
			this.minute.Size = new System.Drawing.Size(68, 17);
			this.minute.TabIndex = 2;
			this.minute.TabStop = true;
			this.minute.Text = "Хвилини";
			this.minute.UseVisualStyleBackColor = true;
			// 
			// day
			// 
			this.day.AutoSize = true;
			this.day.Location = new System.Drawing.Point(108, 44);
			this.day.Name = "day";
			this.day.Size = new System.Drawing.Size(42, 17);
			this.day.TabIndex = 4;
			this.day.TabStop = true;
			this.day.Text = "Дні";
			this.day.UseVisualStyleBackColor = true;
			// 
			// second
			// 
			this.second.AutoSize = true;
			this.second.Location = new System.Drawing.Point(108, 67);
			this.second.Name = "second";
			this.second.Size = new System.Drawing.Size(67, 17);
			this.second.TabIndex = 5;
			this.second.TabStop = true;
			this.second.Text = "Секунди";
			this.second.UseVisualStyleBackColor = true;
			this.second.Click += new System.EventHandler(this.RecalcTime);
			// 
			// TimeToDayForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(292, 260);
			this.Controls.Add(this.choose);
			this.Controls.Add(this.remain);
			this.Controls.Add(this.staticLabel1);
			this.Controls.Add(this.date);
			this.Name = "TimeToDayForm";
			this.Text = "Time";
			this.choose.ResumeLayout(false);
			this.choose.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.DateTimePicker date;
		private System.Windows.Forms.Label staticLabel1;
		private System.Windows.Forms.Label remain;
		private System.Windows.Forms.GroupBox choose;
		private System.Windows.Forms.RadioButton week;
		private System.Windows.Forms.RadioButton year;
		private System.Windows.Forms.RadioButton second;
		private System.Windows.Forms.RadioButton day;
		private System.Windows.Forms.RadioButton mounth;
		private System.Windows.Forms.RadioButton minute;
	}
}