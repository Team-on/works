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

using Fake3D;

namespace ex1 {
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
