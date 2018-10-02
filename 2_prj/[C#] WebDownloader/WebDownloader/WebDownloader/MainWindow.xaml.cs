using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
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


namespace WebDownloader {
	public partial class MainWindow : Window {
		List<FileLink> files = new List<FileLink>();

		public MainWindow() {
			Mutex mutex = new Mutex(true, "WebDownloader", out bool isNew);
			if (!isNew)
				return;

			InitializeComponent();
		}

		private void Window_Loaded(object sender, RoutedEventArgs e) {
			AllocConsole();

			FileLink.path = @"D:\Parser\";
			Directory.CreateDirectory(FileLink.path);
			WebClient client = new WebClient();

			Download("http://avidreaders.ru/books/");

			Console.WriteLine("Файл загружен");

			void Download(string link) {
				FileLink file = new FileLink(link);

				//Console.WriteLine($"{FileLink.path}");
				//Console.WriteLine($"{file.link}");
				//Console.WriteLine($"{file.Path}");
				//Console.WriteLine($"{file.file}");

				using (Stream stream = client.OpenRead(file.link)) {
					using (StreamReader reader = new StreamReader(stream, true)) {
						using (StreamWriter writer = new StreamWriter(file.Path, false, reader.CurrentEncoding)) {
							string line, outLine;
							while ((line = reader.ReadLine()) != null) {
								outLine = line;

								Regex regex = new Regex("src=[\"'](.+?)[\"']");

								foreach (Match i in regex.Matches(line)) {
									int start = i.Value.IndexOfAny(new char[] { '\'', '\"' }) + 1,
										end = i.Value.LastIndexOfAny(new char[] { '\'', '\"' });

									FileLink fileLink = new FileLink(i.Value.Substring(start, end - start));
									Console.WriteLine(fileLink.link);
									outLine = outLine.Substring(0, i.Index) + fileLink.file + outLine.Substring(i.Index + i.Length + 1);
									//Download(fileLink.link);
								}

								writer.WriteLine(outLine);
							}
						}
					}
				}
			}
		}

		[DllImport("kernel32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool AllocConsole();
	}

	class FileLink {
		public static string path;

		public string link;
		public string file;

		public FileLink(string link) {
			this.link = link;
			this.file = link.Substring(link.IndexOf('/') + 2).Replace('/', '\\');
			if (!file.Contains(".html")) {
				if (file[file.Length - 1] == '\\')
					file = file.Substring(0, file.Length - 1);
				file += ".html";
			}

			Directory.CreateDirectory(path + file.Substring(0, file.LastIndexOf("\\")));
		}

		public string Path => path + file;
	}
}
