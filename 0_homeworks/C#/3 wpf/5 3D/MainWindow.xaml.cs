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
using System.Windows.Media.Media3D;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;

namespace Like3D {
	public partial class NativeMethods {
		/// Return Type: BOOL->int  
		///X: int  
		///Y: int  
		[System.Runtime.InteropServices.DllImportAttribute("user32.dll", EntryPoint = "SetCursorPos")]
		[return: System.Runtime.InteropServices.MarshalAsAttribute(System.Runtime.InteropServices.UnmanagedType.Bool)]
		public static extern bool SetCursorPos(int X, int Y);
	}

	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		public MainWindow() {
			InitializeComponent();
		}
		
		private void Window_Loaded(object sender, RoutedEventArgs e) {
			WindowStyle = WindowStyle.None;
			ResizeMode = ResizeMode.NoResize;
			Left = 0;
			Top = 0;
			Width = SystemParameters.VirtualScreenWidth;
			Height = SystemParameters.VirtualScreenHeight;
			Topmost = true;

		}

		private void Window_KeyDown(object sender, KeyEventArgs e) {
			Point3D newPos = camera.Position;
			Vector3D upDir = camera.UpDirection;

			//double angle = Math.Atan2(y2 - y1, x2 - x1) - Math.Atan2(y4 - y3, x4 - x3);

			switch(e.Key) {
			case Key.Escape:
			this.Close();
			break;

			case Key.A:
			newPos.X -= 0.1;
			break;
			case Key.D:
			newPos.X += 0.1;
			break;

			case Key.W:
			newPos.Z -= 0.1;
			break;
			case Key.S:
			newPos.Z += 0.1;
			break;

			case Key.LeftShift:
			newPos.Y -= 0.1;
			break;
			case Key.Space:
			newPos.Y += 0.1;
			break;

			case Key.Q:
			upDir.X -= 0.1;
			break;
			case Key.E:
			upDir.X += 0.1;
			break;
			}
			camera.UpDirection = upDir;
			camera.Position = newPos;
		}

		Point prevMousePos = new Point(0, 0);
		private void Window_MouseMove(object sender, MouseEventArgs e) {
			Mouse.SetCursor(Cursors.None);
			Point currMousePos = e.GetPosition(this);
			if(currMousePos.X == 100 && currMousePos.Y == 100) { 
				prevMousePos = currMousePos;
				return;
			}

			Vector3D lookDir = camera.LookDirection;

			if(currMousePos.X > prevMousePos.X)
				lookDir.X += 0.1;
			else if(currMousePos.X < prevMousePos.X)
				lookDir.X -= 0.1;
			if(currMousePos.Y > prevMousePos.Y)
				lookDir.Y -= 0.1;
			else if(currMousePos.Y < prevMousePos.Y)
				lookDir.Y += 0.1;

			NativeMethods.SetCursorPos(100, 100);

			prevMousePos = currMousePos;
			camera.LookDirection = lookDir;
		}
	}
}