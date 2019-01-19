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
    public partial class MainMenuPage : Page {
        static MainMenuPage mainMenuPage;
        static GamePage gamePage = new GamePage();
        static AchievementsPage achievementsPage = new AchievementsPage();
        static SettingsPage settingsPage = new SettingsPage();
        static CreditsPage creditsPage = new CreditsPage();

        public static MainMenuPage _MainMenuPage => mainMenuPage;
        public static GamePage GamePage => gamePage;
        public static AchievementsPage AchievementsPage => achievementsPage;
        public static SettingsPage SettingsPage => settingsPage;
        public static CreditsPage CreditsPage => creditsPage;

        public MainMenuPage() {
            InitializeComponent();
            mainMenuPage = this;
        }

        private void Play_Click(object sender, RoutedEventArgs e) {
            App.Current.MainWindow.Content = gamePage;
        }

        private void Settings_Click(object sender, RoutedEventArgs e) {
            App.Current.MainWindow.Content = SettingsPage;
        }

        private void Achievements_Click(object sender, RoutedEventArgs e) {
            App.Current.MainWindow.Content = achievementsPage;
        }

        private void Credits_Click(object sender, RoutedEventArgs e) {
            App.Current.MainWindow.Content = creditsPage;
        }

        private void Exit_Click(object sender, RoutedEventArgs e) {
            App.Current.MainWindow.Close();
        }

        private void SetLanguageUa(object sender, RoutedEventArgs e) {
            App.Language = App.Languages[2];
        }

        private void SetLanguageRu(object sender, RoutedEventArgs e) {
            App.Language = App.Languages[1];
        }

        private void SetLanguageEng(object sender, RoutedEventArgs e) {
            App.Language = App.Languages[0];
        }
    }
}
