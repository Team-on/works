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

			TestFill();
		}

		void FilmLeft(object sender, RoutedEventArgs e) {
			if (currFilmId != 0)
				--currFilmId;
			else
				currFilmId = (ushort)( filmController.GetFilmCnt() - 1);
		}

		void FilmRight(object sender, RoutedEventArgs e) {
			if (currFilmId != filmController.GetFilmCnt())
				++currFilmId;
			else
				currFilmId = 0;
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
				"Test Film",
				"src/filmTest.jpg",
				pricesMorning
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 9, 45, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesMorning
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 11, 10, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesMorning
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 12, 0, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 13, 20, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 13, 10, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 15, 45, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Zander,
				new DateTime(2018, 05, 23, 16, 0, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesDay
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 18, 10, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesEvening
				));

			filmController.AddFilm(new FilmInfo(
				ZalInfo.Chaplin,
				new DateTime(2018, 05, 23, 23, 55, 0),
				"Test Film",
				"src/filmTest.jpg",
				pricesNight
				));
		}

		private FilmController filmController;
		ushort currFilmId;
	}
}
