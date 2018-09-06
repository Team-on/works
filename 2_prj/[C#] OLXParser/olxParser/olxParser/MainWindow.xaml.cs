using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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

using HtmlAgilityPack;

namespace olxParser {
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		ObservableCollection<Flat> flats;

		public MainWindow() {
			InitializeComponent();

			flats = new ObservableCollection<Flat>();
			flats.CollectionChanged += (a, b) => dataGrid.Items.Refresh();
			dataGrid.ItemsSource = flats;
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			try {
				string phpArgs = @"page=1";
				string city = @"rovno";
				string url = $@"https://www.olx.ua/nedvizhimost/{city}/?{phpArgs}";
				HtmlWeb web = new HtmlWeb();
				HtmlDocument doc = web.Load(url);

				var nodes = doc.GetElementbyId("offers_table").ChildNodes.FindFirst("tbody").ChildNodes.Where(a=>a.HasClass("wrap"));

				foreach(var node in nodes) {
					var flat = node.ChildNodes.FindFirst("td")
							.ChildNodes.FindFirst("div")
							.ChildNodes.FindFirst("table")
							.ChildNodes.FindFirst("tbody")
							.ChildNodes.FindFirst("tr")
							.ChildNodes.First(a=>a.HasClass("title-cell"))
							.ChildNodes.FindFirst("div")
							.ChildNodes.FindFirst("h3")
							.ChildNodes.FindFirst("a")
						;

					HtmlDocument flatDescription = web.Load(flat.Attributes[0].Value);

					var flattable = flatDescription.GetElementbyId("offerdescription");

					var titlebox = flattable.ChildNodes.FirstOrDefault(a => a.HasClass("offer-titlebox"));
					var infoTable = flattable.ChildNodes.FirstOrDefault(a => a.HasClass("clr descriptioncontent marginbott20"));
					var textcontent = flatDescription.GetElementbyId("textContent");

					var text1 = titlebox.ChildNodes.FindFirst("h1").InnerText;
					var text2 = titlebox.ChildNodes.FirstOrDefault(a => a.HasClass("offer - titlebox__details"))?.InnerText ?? "No info";
					var text3 = infoTable?.InnerText ?? "No info";
					var text4 = textcontent?.InnerText ?? "No info";

					flats.Add(new Flat(text1.Trim(), text2.Trim(), text3.Trim(), text4.Trim()));
				}
			}
			catch(Exception ex) {
				MessageBox.Show($"{ex.Message}\n{ex.StackTrace}", "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
			}
		}
	}
}
