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

using System.Data;
using System.Data.SqlClient;
using System.Data.Entity;

using HtmlAgilityPack;

namespace olxParser {
	class FlatsContext : DbContext {
		public FlatsContext() : base("DbConnection") { }
		public DbSet<Flat> Flats { get; set; }
	}

	public partial class MainWindow : Window {
		FlatsContext db;

		public MainWindow() {
			InitializeComponent();

			var loadWindow = new LoadingWindow();
			loadWindow.Show();
			db = new FlatsContext();
			db.Flats.Load();
			dataGrid.ItemsSource = db.Flats.Local;
			loadWindow.Close();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			Action deleg = ()=> {
				try {
					string phpArgs = @"page=1";
					string city = @"rovno";
					string url = $@"https://www.olx.ua/nedvizhimost/kvartiry-komnaty/prodazha-kvartir-komnat/{city}/?{phpArgs}";
					HtmlWeb web = new HtmlWeb();
					HtmlDocument doc = web.Load(url);

					var nodes = doc.GetElementbyId("offers_table").ChildNodes.FindFirst("tbody").ChildNodes.Where(a => a.HasClass("wrap"));

					foreach(var node in nodes) {
						var flatHtml = node.ChildNodes.FindFirst("td")
								.ChildNodes.FindFirst("div")
								.ChildNodes.FindFirst("table")
								.ChildNodes.FindFirst("tbody")
								.ChildNodes.FindFirst("tr")
								.ChildNodes.First(a => a.HasClass("title-cell"))
								.ChildNodes.FindFirst("div")
								.ChildNodes.FindFirst("h3")
								.ChildNodes.FindFirst("a")
							;

						HtmlDocument flatDescription = web.Load(flatHtml.Attributes[0].Value);

						var flattable = flatDescription.GetElementbyId("offerdescription");

						var titlebox = flattable.ChildNodes.First(a => a.HasClass("offer-titlebox"));
						var infoTable = flattable.ChildNodes.First(a => a.GetClasses().Contains("clr") && a.GetClasses().Contains("descriptioncontent") && a.GetClasses().Contains("marginbott20"))
							.ChildNodes.First(a => a.GetClasses().Contains("details") && a.GetClasses().Contains("fixed") && a.GetClasses().Contains("marginbott20") && a.GetClasses().Contains("margintop5") && a.GetClasses().Contains("full"));
						var textcontent = flatDescription.GetElementbyId("textContent");

						var offerDetails = titlebox.ChildNodes.First(a => a.HasClass("offer-titlebox__details"));
						var dateText = offerDetails.ChildNodes.FindFirst("em").InnerText;
						var start = dateText.IndexOfAny(new char[] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' });
						var end = dateText.LastIndexOf(',') - 1;

						Flat flat = new Flat() {
							Title = titlebox.ChildNodes.FindFirst("h1").InnerText.Trim(),
							City = offerDetails.ChildNodes.FindFirst("a").InnerText.Trim(),
							DateAdd = dateText.Substring(start, end - start),
							Price = flatDescription.GetElementbyId("offeractions").ChildNodes.FindFirst("div").ChildNodes.FindFirst("strong").InnerText,
							Description = textcontent.InnerText.Trim(),
							link = flatHtml.Attributes[0].Value,
						};

						//var attribsTable = .ChildNodes.FindFirst("table");
						foreach(var tr in infoTable.ChildNodes) {
							if(tr.InnerHtml.Trim().Length == 0)
								continue;

							var datacol = tr.ChildNodes.FindFirst("td")
								.ChildNodes.FindFirst("strong");

							string text;
							if(datacol.ChildNodes.Where(a => a.Name == "a").Count() != 0)
								text = datacol.ChildNodes.FindFirst("a").InnerText.Trim();
							else
								text = datacol.InnerText.Trim();

							if(text.Length != 0) {
								switch(tr.ChildNodes.FindFirst("th").InnerText.Trim()) {
								case "Этаж":
								flat.Floor = int.Parse(text);
								break;
								case "Этажность":
								flat.Floors = int.Parse(text);
								break;
								case "Общая площадь":
								//MessageBox.Show(text.Split(' ')[0]);
								flat.Area = double.Parse(text.Split(' ')[0].Replace('.', ','));
								break;
								case "Площадь кухни":
								flat.KitchenArea = double.Parse(text.Split(' ')[0]);
								break;
								case "Количество комнат":
								flat.Rooms = int.Parse(text);
								break;
								}
							}
						}

						System.Windows.Application.Current.Dispatcher.Invoke((Action) delegate {
							if(db.Flats.FirstOrDefault(a => a.link == flat.link) == null) {
								db.Flats.Add(flat);
								dataGrid.Items.Refresh();
							}
						});
					}
				}
				catch(Exception ex) {
					MessageBox.Show($"{ex.Message}\n{ex.StackTrace}", "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
				}

				db.SaveChanges();
			};

			deleg.BeginInvoke(null, null);

		}
	}
}
