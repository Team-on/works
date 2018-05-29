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

namespace WpfApp1 {
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		public MainWindow() {
			InitializeComponent();
			filmController = new FilmController();
			currFilmId = 0;

			places = new Button[Settings.placesInRow.Length][];
			for (int i = 0; i < Settings.placesInRow.Length; ++i) {
				places[i] = new Button[Settings.placesInRow[i]];
				for (int j = 0; j < Settings.placesInRow[i]; ++j) {
					var btn = new Button();
					btn.Content = string.Format($"{i+1}/{j+1}");

					if(i >= 4)
						btn.Background = Brushes.BlueViolet;
					else
						btn.Background = Brushes.Aqua;

					btn.Click += Button_Click;

					places[i][j] = btn;

					PlacesGrid.Children.Add(btn);
					Grid.SetRow(btn, i + 1);
					Grid.SetColumn(btn, j + (14 - Settings.placesInRow[i]) / 2);
				}
			}

			TestFill();
			FillFilmsButton();
		}

		void FilmLeft(object sender, RoutedEventArgs e) {
			if (currFilmId != 0)
				--currFilmId;
			else
				currFilmId = (ushort)( filmController.GetFilmCnt() - 1);
			FillFilmsButton();
		}

		void FilmRight(object sender, RoutedEventArgs e) {
			if (currFilmId != filmController.GetFilmCnt() - 1)
				++currFilmId;
			else
				currFilmId = 0;
			FillFilmsButton();
		}

		void FillFilmsButton() {
			FilmInfo filmInfo = filmController.GetFilmById(currFilmId);
			LabelZal.Content = filmInfo.Zal;
			LabelDate.Content = filmInfo.Time.ToShortDateString() + " " + filmInfo.Time.ToShortTimeString();
			LabelFilmName.Content = filmInfo.Name;

			for(int i = 0; i < filmInfo.places.Length; ++i) {
				for (int j = 0; j < filmInfo.places[i].Length; ++j) {
					places[i][j].Background = filmInfo.places[i][j].isFree ?(i >= 4? Brushes.BlueViolet : Brushes.Aqua) : Brushes.Red;
				}
			}

			ImageTicket.Source = null;
			Place.Content = Row.Content = Film.Content = Zal.Content = Date.Content = Price.Content = "";

			var films = filmController.GetFilmsArray(currFilmId - 1, 3);

			FilmBtn1.Content = new Image {
				Source = new BitmapImage(new Uri(films[0].ImageSrc, UriKind.Relative)),
				Stretch = Stretch.Fill
			};
			FilmBtn2.Content = new Image {
				Source = new BitmapImage(new Uri(films[1].ImageSrc, UriKind.Relative)),
				Stretch = Stretch.Fill
			};
			FilmBtn3.Content = new Image {
				Source = new BitmapImage(new Uri(films[2].ImageSrc, UriKind.Relative)),
				Stretch = Stretch.Fill
			};
		}

		private void Button_Click(object sender, RoutedEventArgs e) {
			string[] b = (e.Source as Button).Content.ToString().Split('/');
			Row.Content = b[0];
			Place.Content = b[1];

			FilmInfo filmInfo = filmController.GetFilmById(currFilmId);

			Film.Content = filmInfo.Name;
			Zal.Content = filmInfo.Zal;
			Date.Content = filmInfo.Time.ToShortDateString() + " " + filmInfo.Time.ToShortTimeString();
			Price.Content = filmInfo.GetPriceByPlace(int.Parse(b[0]) - 1, int.Parse(b[1]) - 1);
			ImageTicket.Source = new BitmapImage(new Uri(filmInfo.ImageSrc, UriKind.Relative));
		}

		private void BuyTicket(object sender, RoutedEventArgs e) {
			if (Place.Content != "" && Row.Content != "") {
				int row = int.Parse(Row.Content as string) - 1, col = int.Parse(Place.Content as string) - 1;
				if (Brushes.Red != places[row][col].Background) {
					FilmInfo filmInfo = filmController.GetFilmById(currFilmId);
					filmInfo.places[row][col].isFree = false;
					places[row][col].Background = Brushes.Red;
					DisplayTicket();
				}
				else
					MessageBox.Show("Це місце вже занято.\nВиберіть інше.", "Увага!", MessageBoxButton.OK, MessageBoxImage.Exclamation, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
			}
		}

		void DisplayTicket() {

		}

		void TestFill() {
			Dictionary<PlaceTypes, ushort> pricesNight = new Dictionary<PlaceTypes, ushort>();
			Dictionary<PlaceTypes, ushort> pricesMorning = new Dictionary<PlaceTypes, ushort>();
			Dictionary<PlaceTypes, ushort> pricesDay = new Dictionary<PlaceTypes, ushort>();
			Dictionary<PlaceTypes, ushort> pricesEvening = new Dictionary<PlaceTypes, ushort>();
			pricesNight[PlaceTypes.Standatd] = 30;
			pricesNight[PlaceTypes.Vip] = 50;
			pricesMorning[PlaceTypes.Standatd] = 40;
			pricesMorning[PlaceTypes.Vip] = 65;
			pricesDay[PlaceTypes.Standatd] = 55;
			pricesDay[PlaceTypes.Vip] = 90;
			pricesEvening[PlaceTypes.Standatd] = 55;
			pricesEvening[PlaceTypes.Vip] = 75;

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 9, 0, 0),
				"Beta test",
				"src/film1.jpg",
				pricesMorning
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 9, 45, 0),
				"Priest",
				"src/film2.jpg",
				pricesMorning
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 11, 10, 0),
				"Abraham Lincoln: vampire hunter",
				"src/film3.jpg",
				pricesMorning
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 12, 0, 0),
				"Day watch",
				"src/film4.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 13, 20, 0),
				"Machete",
				"src/film5.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 13, 10, 0),
				"Machete kills",
				"src/film6.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 15, 45, 0),
				"Ready player one",
				"src/film7.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 16, 0, 0),
				"Van Helsing",
				"src/film8.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 18, 10, 0),
				"Matrix: reloaded",
				"src/film9.jpg",
				pricesEvening
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 23, 55, 0),
				"Warcraft: The begining",
				"src/film10.jpg",
				pricesNight
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 0, 0, 0),
				"Space pirate captain harock",
				"src/film11.jpg",
				pricesNight
				));
		}

		Button[][] places;
		private FilmController filmController;
		ushort currFilmId;
	}
}
