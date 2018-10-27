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

namespace TaoTest {
	public partial class Form1 : Form {
		public Form1() {
			InitializeComponent();
			simpleOpenGlControl1.InitializeContexts();
		}

		private void button2_Click(object sender, EventArgs e) {

		}

		private void button1_Click(object sender, EventArgs e) {

		}

		private void Form1_Load(object sender, EventArgs e) {
			// инициализация Glut 
			Glut.glutInit();
			Glut.glutInitDisplayMode(Glut.GLUT_RGB | Glut.GLUT_DOUBLE | Glut.GLUT_DEPTH);
			// отчитка окна 
			Gl.glClearColor(255, 255, 255, 1);
			// установка порта вывода в соответствии с размерами элемента anT 
			Gl.glViewport(0, 0, simpleOpenGlControl1.Width, simpleOpenGlControl1.Height);
			// настройка проекции
			Gl.glMatrixMode(Gl.GL_PROJECTION);
			Gl.glLoadIdentity();
			Glu.gluPerspective(45, (float)simpleOpenGlControl1.Width / (float)simpleOpenGlControl1.Height, 0.1, 200);
			Gl.glMatrixMode(Gl.GL_MODELVIEW); Gl.glLoadIdentity();
			// настройка параметров OpenGL для визуализации 
			Gl.glEnable(Gl.GL_DEPTH_TEST); 
		}
	}
}
