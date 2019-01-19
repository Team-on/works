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

namespace Ld43.Pages {
    public partial class SettingsPage : Page {
        public SettingsPage() {
            InitializeComponent();
        }

        private void Back_Click(object sender, RoutedEventArgs e) {
            App.Current.MainWindow.Content = MainMenuPage._MainMenuPage;
        }

        private void Window_Activated(object sender, EventArgs e) {
            if (Properties.Settings.Default.IsFullscreen) {
                foreach (var i in resolutinBox.Items) {
                    string[] s = ((i as ComboBoxItem).Content as string).Split('x');
                    int width = int.Parse(s[0]), height = int.Parse(s[1]);
                    if (width == Properties.Settings.Default.WindowWidth && height == Properties.Settings.Default.WindowHeight) {
                        resolutinBox.SelectedItem = i;
                        break;
                    }
                }
            }
            else {
                foreach (var i in resolutinBox.Items) {
                    string[] s = ((i as ComboBoxItem).Content as string).Split('x');
                    int width = int.Parse(s[0]), height = int.Parse(s[1]);
                    if (width == App.Current.MainWindow.Width && height == App.Current.MainWindow.Height) {
                        resolutinBox.SelectedItem = i;
                        break;
                    }
                }
            }

            isFullscreen.IsChecked = Properties.Settings.Default.IsFullscreen;
            resolutinBox.IsEnabled = !Properties.Settings.Default.IsFullscreen;
        }
        private void Page_Loaded(object sender, RoutedEventArgs e) => Window_Activated(sender, e);


        private void resolutinBox_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            string[] s = ((e.AddedItems[0] as ComboBoxItem).Content as string).Split('x');
            int width = int.Parse(s[0]), height = int.Parse(s[1]);

            App.Current.MainWindow.Width = Ld43.Properties.Settings.Default.WindowWidth = width;
            App.Current.MainWindow.Height = Ld43.Properties.Settings.Default.WindowHeight = height;
        }

        private void isFullscreen_Checked(object sender, RoutedEventArgs e) {
            Ld43.Properties.Settings.Default.IsFullscreen = true;
            (App.Current.MainWindow as MainWindow)?.OpenFullScreen();
            resolutinBox.IsEnabled = false;
            Properties.Settings.Default.IsFullscreen = isFullscreen.IsChecked.Value;
        }

        private void isFullscreen_Unchecked(object sender, RoutedEventArgs e) {
            Ld43.Properties.Settings.Default.IsFullscreen = false;
            (App.Current.MainWindow as MainWindow)?.OpenNonFullScreen();
            resolutinBox.IsEnabled = true;
            Properties.Settings.Default.IsFullscreen = isFullscreen.IsChecked.Value;
        }
    }
}
