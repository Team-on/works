using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

namespace FileLocker {
	static class Program {
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() {
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);

			ContextMenu contextMenu = new ContextMenu();

			MenuItem menuItem = new MenuItem() {
				Index = 0,
				Text = "Add file",
			};
			menuItem.Click += AddFile;
			contextMenu.MenuItems.Add(menuItem);

			menuItem = new MenuItem() {
				Index = 1,
				Text = "Show control panel",
			};
			menuItem.Click += ShowForm;
			contextMenu.MenuItems.Add(menuItem);

			menuItem = new MenuItem() {
				Index = 2,
				Text = "Exit",
			};
			menuItem.Click += CloseApp;
			contextMenu.MenuItems.Add(menuItem);


			NotifyIcon notifyIcon = new NotifyIcon {
				Icon = new Icon(@"Resources\icon.ico"),
				Text = "FileLocker",
				ContextMenu = contextMenu,
				Visible = true,
			};
			notifyIcon.DoubleClick += ShowForm;


			Application.Run();

			//notifyIcon.Visible = false;
		}

		static void CloseApp(object Sender, EventArgs e) {
			Application.Exit();
		}

		public static Lazy<OpenFileDialog> fileDialog = new Lazy<OpenFileDialog>(()=>new OpenFileDialog() { Multiselect = false});
		static Lazy<LockListWindow> form = new Lazy<LockListWindow>();
		static void ShowForm(object Sender, EventArgs e) {
			form.Value.Show();
		}

		static void AddFile(object Sender, EventArgs e) {
			if (fileDialog.Value.ShowDialog() == DialogResult.OK) {
				string s = fileDialog.Value.FileName;
			}
		}
	}
}
