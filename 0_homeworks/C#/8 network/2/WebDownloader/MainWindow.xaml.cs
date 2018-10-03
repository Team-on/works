using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Xml;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Windows.Forms;


namespace WebDownloader {
	public partial class MainWindow : Window {
		public MainWindow() {
			Mutex mutex = new Mutex(true, "WebDownloader", out bool isNew);
			if (!isNew)
				return;

			AllocConsole();
			InitializeComponent();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			var grid = new Grid();
			grid.Children.Add(new System.Windows.Controls.Label() { Content = "asgasg" });

			listBox.Items.Add(new ListBoxItem() {
				Content = grid,
			});


			Parse();
		}

		private void Parse() {
			WebClient client = new WebClient();

			Console.WriteLine("Download");
			try {
				HttpClient hc = new HttpClient();
				HttpResponseMessage result = hc.GetAsync("http://avidreaders.ru/books/index.html").GetAwaiter().GetResult();

				Stream stream = result.Content.ReadAsStreamAsync().GetAwaiter().GetResult();

				//Console.WriteLine(result.Content.Read);
				//HtmlDocument doc = new HtmlDocument();
				//doc.Load(stream);

				Console.WriteLine("End:");
			}
			catch (Exception ex) {
				Console.WriteLine(ex.Message);
			}
			finally {
			}

			//HttpClient hc = new HttpClient();
			//HttpResponseMessage result = hc.GetAsync("http://avidreaders.ru/books/index.html").GetAwaiter().GetResult();

			//using (Stream stream = result.Content.ReadAsStreamAsync().GetAwaiter().GetResult()) {
			//	HtmlDocument doc;
			//	var d = new XmlDocument();
			//	doc.Load(stream);

			//	HtmlNodeCollection links = doc.DocumentNode.SelectNodes("//a[@href]");//the parameter is use xpath see: https://www.w3schools.com/xml/xml_xpath.asp 

			//	using (StreamReader reader = new StreamReader(stream)) {
			//		string line = "";
			//		while ((line = reader.ReadLine()) != null) {
			//			Console.WriteLine(line);
			//		}
			//	}
			//}
		}


		[DllImport("kernel32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool AllocConsole();
	}
}
