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

			Database.SetInitializer<FlatsContext>(new DropCreateDatabaseIfModelChanges<FlatsContext>());

			db = new FlatsContext();
			//db.Database.Delete();
			//db.Database.Create();
			db.Flats.Load();
			dataGrid.ItemsSource = db.Flats.Local;
			loadWindow.Close();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			Action deleg = () => {
				//Parsing parsing = new Parsing();
				//parsing.Show();

				try {
					HtmlWeb web = new HtmlWeb();
					string city = @"rovno";
					HtmlDocument doc = web.Load($@"https://www.olx.ua/nedvizhimost/kvartiry-komnaty/prodazha-kvartir-komnat/{city}");

					int maxPage = 0;
					//doc.GetElementbyId("body-container").ChildNodes.First(a => {
					//	try {
					//		MessageBox.Show(a.OuterHtml);
					//		if(a.Name == "div" && a.HasClass("wrapper")) {
					//			foreach(var child in a.ChildNodes) {
					//				if(child.HasClass("content")) {
					//					foreach(var b in child.ChildNodes) {
					//						if(b.HasClass("pager") && b.HasClass("rel") && b.HasClass("clr")) {
					//							foreach(var c in b.Descendants("a")) {
					//								foreach(var attr in c.Attributes) {
					//									if(attr.Name == "data-cy" && attr.Value == "page-link-last") {
					//										maxPage = int.Parse(c.ChildNodes.FindFirst("span").InnerText);
					//										return true;
					//									}
					//								}
					//							}
					//						}
					//					}
					//				}
					//			}
					//		}
					//	}
					//	catch(Exception ex) {
					//		MessageBox.Show($"{ex.Message}\n{ex.StackTrace}", "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
					//	}
					//	return false;
					//});

					doc.DocumentNode.Descendants("a").First(a=> {
						foreach(var attr in a.Attributes) {
							if(attr.Name == "data-cy" && attr.Value == "page-link-last") {
								maxPage = int.Parse(a.ChildNodes.FindFirst("span").InnerText);
								return true;
							}
						}
						return false;
					});

					if(maxPage > 10)
						maxPage = 10;
					while(maxPage != 0) {
						doc = web.Load($@"https://www.olx.ua/nedvizhimost/kvartiry-komnaty/prodazha-kvartir-komnat/{city}/?page={maxPage}");

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
							var end = dateText.LastIndexOf(',');

							var price = flatDescription.GetElementbyId("offeractions").ChildNodes.FindFirst("div").ChildNodes.FindFirst("strong").InnerText;
							var priceArr = price.Split(' ');
							int priceNum = 0;
							string priceSym = "";
							foreach(var i in priceArr) {
								foreach(var c in i) {
									if(char.IsDigit(c))
										priceNum = priceNum * 10 + c - '0';
									else
										priceSym += c;
								}
							}

							Flat flat = new Flat() {
								Title = titlebox.ChildNodes.FindFirst("h1").InnerText.Trim(),
								City = offerDetails.ChildNodes.FindFirst("a").InnerText.Trim(),
								DateAdd = dateText.Substring(start, end - start),
								Price = priceNum,
								PriceSymbol = priceSym,
								//Description OFF
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
									flat.KitchenArea = double.Parse(text.Split(' ')[0].Replace('.', ','));
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

						--maxPage;
					}
				}
				catch(Exception ex) {
					MessageBox.Show($"{ex.Message}\n{ex.StackTrace}", "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
				}

				db.SaveChanges();
				//parsing.Close();
			};

			deleg.BeginInvoke(null, null);

		}
	}
}
