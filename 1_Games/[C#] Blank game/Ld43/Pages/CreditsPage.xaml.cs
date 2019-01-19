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
    public partial class CreditsPage : Page {
        public CreditsPage() {
            InitializeComponent();
        }

        private void Back_Click(object sender, RoutedEventArgs e) {
            App.Current.MainWindow.Content = MainMenuPage._MainMenuPage;
        }
    }
}
