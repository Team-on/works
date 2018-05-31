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


namespace GraphSity {
	public partial class MainWindow : Window {
		CurrentMode currMode;
		NodesControl nodes;

		public MainWindow() {
			InitializeComponent();
			nodes = new NodesControl();
			currMode = CurrentMode.None;

			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();
			//nodes.AddNode();

			//nodes.AddPath(0, 1, 10);
			//nodes.AddPath(0, 2, 30);
			//nodes.AddPath(0, 4, 40);
			//nodes.AddPath(1, 2, 20);
			//nodes.AddPath(1, 3, 20);
			//nodes.AddPath(3, 2, 5);
			//nodes.AddPath(4, 3, 10);

			//nodes.AddPath(0, 4, 40);
			//nodes.AddPath(0, 3, 80);
			//nodes.AddPath(0, 1, 10);
			//nodes.AddPath(1, 4, 20);
			//nodes.AddPath(1, 2, 20);
			//nodes.AddPath(2, 3, 14);
			//nodes.AddPath(4, 3, 30);

			//nodes.AddPath(0, 1, 10);
			//nodes.AddPath(0, 2, 20);
			//nodes.AddPath(0, 5, 100);

			//nodes.AddPath(1, 3, 80);
			//nodes.AddPath(1, 4, 60);

			//nodes.AddPath(2, 1, 70);
			//nodes.AddPath(2, 3, 70);

			//nodes.AddPath(3, 5, 75);

			//nodes.AddPath(4, 5, 60);
		}


		private void AddSityMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.AddSity) {
				currMode = CurrentMode.AddSity;
				this.Cursor = Cursors.Hand;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void RemoveSityMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.RemoveSity) {
				currMode = CurrentMode.RemoveSity;
				this.Cursor = Cursors.No;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void AddPathMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.AddPath) {
				currMode = CurrentMode.AddPath;
				this.Cursor = Cursors.Cross;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void RemovePathMode(object sender, RoutedEventArgs e) {
			if (currMode != CurrentMode.RemovePath) {
				currMode = CurrentMode.RemovePath;
				this.Cursor = Cursors.Help;
			}
			else {
				currMode = CurrentMode.None;
				this.Cursor = Cursors.Arrow;
			}
		}

		private void Field_MouseLeftButtonDown(object sender, MouseButtonEventArgs e) {
			switch (currMode) {
			case CurrentMode.AddSity:
			nodes.AddNode();
			break;
			case CurrentMode.RemoveSity:
			break;
			case CurrentMode.AddPath:
			break;
			case CurrentMode.RemovePath:
			break;
			case CurrentMode.None:
			break;
			}
		}

		private void Window_SizeChanged(object sender, SizeChangedEventArgs e) {
			fieldBackground.Height = e.NewSize.Height - statusBar.ActualHeight - this.menuStrip.ActualHeight - 30;
			fieldBackground.Width = e.NewSize.Width - GridWithInfo.Width - 10;
		}
	}

}
