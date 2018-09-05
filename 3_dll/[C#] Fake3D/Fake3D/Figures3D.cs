using System;
using System.Windows.Media;
using System.Windows.Shapes;

using static System.Math;

namespace Fake3D {
	internal static class NumericExtensions {
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
}