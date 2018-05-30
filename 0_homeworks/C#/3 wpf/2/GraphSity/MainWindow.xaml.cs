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

		private void Field_MouseUp(object sender, MouseButtonEventArgs e) {
			MessageBox.Show("Press");

			switch (currMode) {
			case CurrentMode.AddSity:
			break;
			case CurrentMode.RemoveSity:
			break;
			case CurrentMode.AddPath:
			break;
			case CurrentMode.RemovePath:
			break;
			}
		}

		private void field_MouseMove(object sender, MouseEventArgs e) {
			MessageBox.Show("Press");
		}
	}

}
