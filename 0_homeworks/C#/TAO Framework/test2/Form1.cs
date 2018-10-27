using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Tao.FreeGlut;
using Tao.OpenGl;
using Tao.Platform.Windows;

namespace test2 {
	public partial class Form1 : Form {
		public Form1() {
			InitializeComponent();
			a.InitializeContexts();
		}

		private void Form1_Load(object sender, EventArgs e) {
			Glut.glutInit();
			Glut.glutInitDisplayMode(Glut.GLUT_RGB | Glut.GLUT_DOUBLE | Glut.GLUT_DEPTH);

			Gl.glClearColor(255, 255, 255, 1);
			
			Gl.glViewport(0, 0, a.Width, a.Height);

			Gl.glMatrixMode(Gl.GL_PROJECTION);
			Gl.glLoadIdentity();
			Glu.gluPerspective(45, a.Width / a.Height, 0.1, 200);
			Gl.glMatrixMode(Gl.GL_MODELVIEW);
			Gl.glLoadIdentity();

			Gl.glEnable(Gl.GL_DEPTH_TEST);
		}

		private void button1_Click(object sender, EventArgs e) {
			Gl.glClear(Gl.GL_COLOR_BUFFER_BIT | Gl.GL_DEPTH_BUFFER_BIT);
			Gl.glLoadIdentity();
			Gl.glColor3f(1.0f, 0, 0);
			Gl.glPushMatrix();
			Gl.glTranslated(0, 0, -6);
			Gl.glRotated(45, 1, 1, 0);
			Glut.glutWireSphere(2, 32, 32);
			Gl.glPopMatrix();
			Gl.glFlush();
			a.Invalidate();
		}

		private void button2_Click(object sender, EventArgs e) {
			Application.Exit();
		}
	}
}
