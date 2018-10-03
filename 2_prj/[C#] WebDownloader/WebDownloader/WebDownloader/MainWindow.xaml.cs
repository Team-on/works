using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace WebDownloader {
	public partial class MainWindow : Window {
		public MainWindow() {
			Mutex mutex = new Mutex(true, "WebDownloader", out bool isNew);
			if (!isNew)
				return;

			InitializeComponent();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			var grid = new Grid();
			grid.Children.Add(new Label() { Content = "asgasg" });

			listBox.Items.Add(new ListBoxItem() {
				Content = grid,
			});
		}


		[DllImport("kernel32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool AllocConsole();
	}
}
