using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using static System.Math;

namespace Like3D {
	public static class NumericExtensions {
		public static double ToRadians(this double val) => (PI / 180) * val;
	}

	public class Point3D {
		public double x, y, z;

		public Point3D() {
			x = y = z = 0;
		}

		public Point3D(double x, double y, double z) {
			this.x = x;
			this.y = y;
			this.z = z;
		}
	}

	public class Line3D {
		Line line2d;
		Point3D p1, p2;

		internal Line3D() {
			p1 = new Point3D();
			p2 = new Point3D();
		}

		public Line3D(double x1, double y1, double z1, double x2, double y2, double z2) : this() {
			line2d = new Line() {
				StrokeThickness = 2,
				Stroke = Brushes.Black,
				StrokeStartLineCap = PenLineCap.Flat,
				StrokeEndLineCap = PenLineCap.Flat,
			};
			p1.x = x1;
			p1.y = y1;
			p1.z = z1;
			p2.x = x2;
			p2.y = y2;
			p2.z = z2;
		}

		public Line3D(Point3D p1, Point3D p2) : this() {
			this.p1.x = p1.x;
			this.p1.y = p1.y;
			this.p2.x = p2.x;
			this.p2.y = p2.y;
		}

		public void Recalc2DLine(double c1, double q1, double r1, double c2, double q2, double r2) {
			line2d.X1 = c1 * p1.x + q1 * p1.y + r1 * p1.z;
			line2d.X2 = c1 * p2.x + q1 * p2.y + r1 * p2.z;
			line2d.Y1 = c2 * p1.x + q2 * p1.y + r2 * p1.z;
			line2d.Y2 = c2 * p2.x + q2 * p2.y + r2 * p2.z;
		}

		public static void CalcValues(out double c1, out double q1, out double r1, out double c2, out double q2, out double r2, double a, double b, double c) {
			a = a.ToRadians();
			b = b.ToRadians();
			c = c.ToRadians();

			c1 = Cos(b) * Cos(c);
			q1 = -Sin(c) * Cos(b);
			r1 = Sin(b);
			c2 = Cos(c) * -Sin(b) * -Sin(a) + Sin(c) * Cos(a);
			q2 = -Sin(c) * -Sin(b) * -Sin(a) + Cos(c) * Cos(a);
			r2 = Cos(b) * -Sin(a);
		}

		public Line Get2DLine() => line2d;
	}

	public class Cube3D {
		Line3D[] lines;

		public Cube3D(double x1, double y1, double z1, double x2, double y2, double z2) {
			lines = new Line3D[12];
			lines[0] = new Line3D(x1, y1, z1, x2, y1, z1);
			lines[1] = new Line3D(x1, y1, z1, x1, y2, z1);
			lines[2] = new Line3D(x2, y2, z1, x2, y1, z1);
			lines[3] = new Line3D(x2, y2, z1, x1, y2, z1);

			lines[4] = new Line3D(x1, y1, z2, x2, y1, z2);
			lines[5] = new Line3D(x1, y1, z2, x1, y2, z2);
			lines[6] = new Line3D(x2, y2, z2, x2, y1, z2);
			lines[7] = new Line3D(x2, y2, z2, x1, y2, z2);

			lines[8] =  new Line3D(x1, y1, z1, x1, y1, z2);
			lines[9] =  new Line3D(x1, y2, z1, x1, y2, z2);
			lines[10] = new Line3D(x2, y1, z1, x2, y1, z2);
			lines[11] = new Line3D(x2, y2, z1, x2, y2, z2);
		}

		public Line3D[] GetLines() => lines;
	}

	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		List<Line3D> lines3D = new List<Line3D> {
			/*
			//Піраміда
			new Line3D(-100, -100, -100, -100,  100, -100),
			new Line3D(-100, -100, -100,  100, -100, -100),

			new Line3D(100, 100, -100, -100,  100, -100),
			new Line3D(100, 100, -100,  100, -100, -100),

			new Line3D(0, 0, 100,  100,  100, -100),
			new Line3D(0, 0, 100, -100,  100, -100),
			new Line3D(0, 0, 100,  100, -100, -100),
			new Line3D(0, 0, 100, -100, -100, -100),
			*/

			/*
			//Куб
			new Line3D(-100, -100, -100, -100,  100, -100),
			new Line3D(-100, -100, -100,  100, -100, -100),
			new Line3D(100, 100, -100, -100,  100, -100),
			new Line3D(100, 100, -100,  100, -100, -100),

			new Line3D(-100, -100, 100, -100,  100, 100),
			new Line3D(-100, -100, 100,  100, -100, 100),
			new Line3D(100, 100, 100, -100,  100, 100),
			new Line3D(100, 100, 100,  100, -100, 100),

			new Line3D(-100, -100, -100, -100, -100, 100),
			new Line3D(100, -100, -100, 100, -100, 100),
			new Line3D(-100, 100, -100, -100, 100, 100),
			new Line3D(100, 100, -100, 100,  100, 100),
			*/
		};

		public MainWindow() {
			InitializeComponent();

			var body = new Cube3D(-40, -50, -25, 40, 70, 25);
			lines3D.AddRange(body.GetLines());

			var head = new Cube3D(-20, -50, -25, 20, -90, 25);
			lines3D.AddRange(head.GetLines());

			var leye = new Cube3D(-15, -80, -25, -2, -75, -25);
			lines3D.AddRange(leye.GetLines());

			var reye = new Cube3D(2, -80, -25, 15, -75, -25);
			lines3D.AddRange(reye.GetLines());

			var larm = new Cube3D(40, -50, -12, 60, 40, 12);
			lines3D.AddRange(larm.GetLines());

			var rarm = new Cube3D(-40, -50, -12, -60, 40, 12);
			lines3D.AddRange(rarm.GetLines());

			var lleg = new Cube3D(-30, 70, -14, -10, 170, 14);
			lines3D.AddRange(lleg.GetLines());

			var rleg = new Cube3D(10, 70, -14, 30, 170, 14);
			lines3D.AddRange(rleg.GetLines());
		}

		private void sliderz_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
			labelz.Content = "Z: " + sliderz.Value.ToString();
			Line3D.CalcValues(out double p1, out double q1, out double r1, out double p2, out double q2, out double r2, sliderx.Value, slidery.Value, sliderz.Value);
			foreach(var line in lines3D)
				line.Recalc2DLine(p1, q1, r1, p2, q2, r2);
			this.Title = string.Format("{0:0.##} {1:0.##} {2:0.##} {3:0.##} {4:0.##} {5:0.##}", p1, p2, q1, q2, r1, r2);
		}

		private void slidery_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
			labely.Content = "Y: " + slidery.Value.ToString();
			Line3D.CalcValues(out double p1, out double q1, out double r1, out double p2, out double q2, out double r2, sliderx.Value, slidery.Value, sliderz.Value);
			foreach(var line in lines3D)
				line.Recalc2DLine(p1, q1, r1, p2, q2, r2);
			this.Title = string.Format("{0:0.##} {1:0.##} {2:0.##} {3:0.##} {4:0.##} {5:0.##}", p1, p2, q1, q2, r1, r2);
		}

		private void sliderx_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
			labelx.Content = "X: " + sliderx.Value.ToString();
			Line3D.CalcValues(out double p1, out double q1, out double r1, out double p2, out double q2, out double r2, sliderx.Value, slidery.Value, sliderz.Value);
			foreach(var line in lines3D)
				line.Recalc2DLine(p1, q1, r1, p2, q2, r2);
			this.Title = string.Format("{0:0.##} {1:0.##} {2:0.##} {3:0.##} {4:0.##} {5:0.##}", p1, p2, q1, q2, r1, r2);
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			Line3D.CalcValues(out double p1, out double q1, out double r1, out double p2, out double q2, out double r2, sliderx.Value, slidery.Value, sliderz.Value);
			foreach(var line in lines3D) {
				canvas.Children.Add(line.Get2DLine());
				line.Recalc2DLine(p1, q1, r1, p2, q2, r2);
			}
		}
	}
}