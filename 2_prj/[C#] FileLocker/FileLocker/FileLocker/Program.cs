using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows.Forms;

using Microsoft.Win32;

namespace FileLocker {
	static class Program {
		public static Lazy<OpenFileDialog> fileDialog = new Lazy<OpenFileDialog>(() => new OpenFileDialog() { Multiselect = false });
		public static FileLocker fileLocker = new FileLocker();

		static Lazy<LockListWindow> form = new Lazy<LockListWindow>();
		static Mutex mutex;

		[STAThread]
		static void Main() {
			Mutex mutex = new Mutex(true, "FileLocker", out bool isNew);
			if (!isNew)
				return;

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
				Text = "Add to auto launch",
			};
			menuItem.Click += AddToStartup;
			contextMenu.MenuItems.Add(menuItem);

			menuItem = new MenuItem() {
				Index = 3,
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

			Hooker.SetHook();
			Application.Run();

			//notifyIcon.Visible = false;
		}

		static void CloseApp(object Sender, EventArgs e) {
			fileLocker.UnlockAll();
			Hooker.UnsetHook();
			Application.Exit();
		}

		static void ShowForm(object Sender, EventArgs e) {
			form.Value.Show();
		}

		static void AddFile(object Sender, EventArgs e) {
			if (fileDialog.Value.ShowDialog() == DialogResult.OK) {
				fileLocker.AddFile(fileDialog.Value.FileName);
			}
		}

		static void AddToStartup(object Sender, EventArgs e) {
			RegistryKey rk = Registry.CurrentUser.OpenSubKey("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);
			rk.SetValue("FileLocker", Application.ExecutablePath);
		}
	}
}
