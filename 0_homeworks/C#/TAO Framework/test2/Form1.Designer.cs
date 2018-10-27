namespace test2 {
	partial class Form1 {
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
			this.a = new Tao.Platform.Windows.SimpleOpenGlControl();
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// a
			// 
			this.a.AccumBits = ((byte)(0));
			this.a.AutoCheckErrors = false;
			this.a.AutoFinish = false;
			this.a.AutoMakeCurrent = true;
			this.a.AutoSwapBuffers = true;
			this.a.BackColor = System.Drawing.Color.Black;
			this.a.ColorBits = ((byte)(32));
			this.a.DepthBits = ((byte)(16));
			this.a.Location = new System.Drawing.Point(13, 13);
			this.a.Name = "a";
			this.a.Size = new System.Drawing.Size(668, 425);
			this.a.StencilBits = ((byte)(0));
			this.a.TabIndex = 0;
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(688, 13);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 1;
			this.button1.Text = "button1";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(688, 43);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(75, 23);
			this.button2.TabIndex = 2;
			this.button2.Text = "button2";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.a);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

		}

		#endregion

		private Tao.Platform.Windows.SimpleOpenGlControl a;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button2;
	}
}

