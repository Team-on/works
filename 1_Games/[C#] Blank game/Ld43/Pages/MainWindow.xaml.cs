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
using System.Windows.Shapes;

namespace Ld43.Pages {
    public partial class MainWindow : Window {
        public MainWindow() {
            InitializeComponent();

            if (Properties.Settings.Default.IsFullscreen)
                OpenFullScreen();
            else
                OpenNonFullScreen();

            App.Current.MainWindow = this;
        }

		private void Window_Closed(object sender, EventArgs e) {
			App.Current.MainWindow.Close();
		}

		public void OpenFullScreen() {
            WindowStyle = WindowStyle.None;
            WindowState = WindowState.Maximized;

            Left = 0;
            Top = 0;
            Width = SystemParameters.VirtualScreenWidth;
            Height = SystemParameters.VirtualScreenHeight;

            Topmost = true;
        }

        public void OpenNonFullScreen() {
            WindowStyle = WindowStyle.SingleBorderWindow;
            WindowState = WindowState.Normal;

            Width = Properties.Settings.Default.WindowWidth;
            Height = Properties.Settings.Default.WindowHeight;
            Left = (SystemParameters.VirtualScreenWidth - Width) / 2;
            Top = (SystemParameters.VirtualScreenHeight - Height) / 2;

            Topmost = false;
        }
    }
}
