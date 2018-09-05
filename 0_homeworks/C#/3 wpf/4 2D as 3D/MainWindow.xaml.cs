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

	public class Line3D {
		Line line2d;
		double x1, y1, x2, y2, z1, z2;

		public Line3D(double x1, double y1, double z1, double x2, double y2, double z2) {
			line2d = new Line() {
				StrokeThickness = 2,
				Stroke = Brushes.Black,
				StrokeStartLineCap = PenLineCap.Flat,
				StrokeEndLineCap = PenLineCap.Flat,
			};
			this.x1 = x1;
			this.y1 = y1;
			this.z1 = z1;
			this.x2 = x2;
			this.y2 = y2;
			this.z2 = z2;
		}

		public void Recalc2DLine(double p1, double q1, double r1, double p2, double q2, double r2) {
			line2d.X1 = p1 * x1 + q1 * y1 + r1 * z1;
			line2d.X2 = p1 * x2 + q1 * y2 + r1 * z2;
			line2d.Y1 = p2 * x1 + q2 * y1 + r2 * z1;
			line2d.Y2 = p2 * x2 + q2 * y2 + r2 * z2;
		}

		public static void CalcValues(out double p1, out double q1, out double r1, out double p2, out double q2, out double r2, double a, double b, double c) {
			a = a.ToRadians();
			b = b.ToRadians();
			c = c.ToRadians();

			p1 = Cos(b) * Cos(c);
			q1 = -Sin(c) * Cos(b);
			r1 = Sin(b);
			p2 = Cos(c) * -Sin(b) * -Sin(a) + Sin(c) * Cos(a);
			q2 = -Sin(c) * -Sin(b) * -Sin(a) + Cos(c) * Cos(a);
			r2 = Cos(b) * -Sin(a);
		}

		public Line Get2DLine() => line2d;
	}

	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		Line3D[] lines3D = new Line3D[] {
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

			new Line3D(-50, -50, 25, -50,  100, 25),
			new Line3D(-50, -50, 25,  25, -50, 25),
			new Line3D(25, 100, 25, -50,  100, 25),
			new Line3D(25, 100, 25,  25, -50, 25),

			new Line3D(-50, -50, -25, -50,  100, -25),
			new Line3D(-50, -50, -25,  25, -50, -25),
			new Line3D(25, 100, -25, -50,  100, -25),
			new Line3D(25, 100, -25,  25, -50, -25),

			new Line3D(-50, -50, 25, -50, -50, -25),
			new Line3D(25, 100, 25, 25, 100, -25),
			new Line3D(25, -50, 25, 25, -50, -25),
			new Line3D(-50,  100, 25, -50,  100, -25),

		};

		public MainWindow() {
			InitializeComponent();
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