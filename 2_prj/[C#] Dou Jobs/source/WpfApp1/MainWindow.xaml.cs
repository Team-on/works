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

using HtmlAgilityPack;

using System.Data;
using System.Data.Entity;

namespace WpfApp1 {
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window {
		Parser parser;


		public MainWindow() {
			Database.SetInitializer<VacancyContext>(new DropCreateDatabaseIfModelChanges<VacancyContext>());

			InitializeComponent();
			startSearchBoxText = searchTextBox.Text;
			startSearchBoxForeground = searchTextBox.Foreground;

			parser = new Parser();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			HtmlDocument doc = new HtmlWeb().Load("https://jobs.dou.ua/vacancies/");

			foreach (var node in doc.DocumentNode.Descendants("select")
				.First((a) => a.GetAttributeValue("name", "n") == "category").Descendants("option")) {
				string attrVal = node.GetAttributeValue("value", "n");
				if (attrVal != "" && attrVal != "n")
					categoryItems.Items.Add(attrVal);
				else
					categoryItems.Items.Add(node.InnerText);
			}
			categoryItems.SelectedIndex = 0;

			cityItems.Items.Add("Все города");
			foreach (var node in doc.DocumentNode.Descendants("ul")
				.First((a) => a.HasClass("other")).Descendants("li")) {
				cityItems.Items.Add(node.ChildNodes.FindFirst("a").InnerText);
			}
			cityItems.SelectedIndex = 0;
		}

		private void searchTextBox_KeyDown(object sender, KeyEventArgs e) {
			if (searchTextBox.Text == startSearchBoxText) {
				searchTextBox.Text = "";
				searchTextBox.Foreground = Brushes.Black;
			}
		}

		private void searchTextBox_MouseLeftButtonDown(object sender, MouseButtonEventArgs e) {
			if (searchTextBox.Text == startSearchBoxText) {
				searchTextBox.SelectionStart = 0;
				searchTextBox.SelectionLength = searchTextBox.Text.Length;
			}
		}

		private void Parse_Click(object sender, RoutedEventArgs e) {
			Action ac = new Action(() => {
                byte[] padSize = {8, 10, 32, 32, 10, 20, 0 };


				Application.Current.Dispatcher.Invoke(() => Parse.IsEnabled = false);

				parser.Parse(searchTextBox.Text == startSearchBoxText ? null : searchTextBox.Text,
				categoryItems.SelectedIndex == 0 ? "" : (string)categoryItems.SelectedItem,
				cityItems.SelectedIndex == 0 ? "" : (string)cityItems.SelectedItem);

				bool background = false;
				listBox.Items.Clear();

				foreach (var vac in parser.Parsed) {
					ListBoxItem item = new ListBoxItem() { Background = background ? Brushes.LightGray : Brushes.White };
					Grid grid = new Grid();

					//grid.Children.Add(new TextBlock() { Text=vac.Id.ToString() });
					//Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
					grid.Children.Add(new TextBlock() { Text = vac.IdDou.ToString() });
					Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
					grid.Children.Add(new TextBlock() { Text = vac.Date ?? "NULL" });
					Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
					grid.Children.Add(new TextBlock() { Text = vac.Title ?? "NULL" });
					Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
					grid.Children.Add(new TextBlock() { Text = vac.Company ?? "NULL" });
					Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
					grid.Children.Add(new TextBlock() { Text = vac.Salary ?? "NULL" });
					Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
					grid.Children.Add(new TextBlock() { Text = vac.City ?? "NULL" });
					Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
					grid.Children.Add(new TextBlock() { Text = vac.Link ?? "NULL" });
					Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
                    //grid.Children.Add(new TextBlock() { Text = vac.ShortDescription?? "NULL" });
                    //Grid.SetColumn(grid.Children[grid.Children.Count - 1], grid.Children.Count - 1);
                    grid.Tag = vac;

                    for (byte i = 0; i < grid.Children.Count; ++i) {
                        double width = padSize[i] * 5;
                        if (width == 0)
                            grid.ColumnDefinitions.Add(new ColumnDefinition());
                        else
                           grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(width, GridUnitType.Pixel) });
                        if (grid.Children[i] is FrameworkElement elem)
                            elem.Margin = new Thickness(10, 0, 10, 0);
                        if (grid.Children[i] is TextBlock tb)
                            tb.Text = tb.Text.Pad(padSize[i]);

                    }

                    item.Content = grid;
					listBox.Items.Add(item);

					background = !background;
				} 

				Application.Current.Dispatcher.Invoke(() => Parse.IsEnabled = true);
			});

			//ac.BeginInvoke(null, null);
			ac();

            //searchTextBox.Text = startSearchBoxText;
            //searchTextBox.Foreground = startSearchBoxForeground;
        }

		string startSearchBoxText;
		Brush startSearchBoxForeground;

        private void listBox_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (listBox.SelectedItem == null)
                return;

            if(e.LeftButton == MouseButtonState.Pressed)
            {
                new VacancyInfo(((listBox.SelectedItem as ListBoxItem).Content as Grid).Tag as Vacancy).Show();
            }
        }
    }
}
