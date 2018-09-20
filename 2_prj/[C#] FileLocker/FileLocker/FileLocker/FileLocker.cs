using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace FileLocker {
	class FileLocker {
		List<Thread> threads = new List<Thread>();

		public FileLocker() {
			//Properties.Settings.Default.Files.Clear();
			//Properties.Settings.Default.Save();
			foreach (var i in Properties.Settings.Default.Files)
				_AddFile(i);
		}

		public void Unlock(int id) {
			threads[id].Abort();
		}

		public void Lock(int id) {
			threads[id].Start();
		}

		public void UnlockAll() {
			foreach (var i in threads) 
				if (i.IsAlive) 
					i.Abort();
		}

		void _AddFile(string filePath) {
			Thread t = new Thread((a) => {
				try {
					File.Open(a as string, FileMode.Open);
					while (true) {
						Thread.Sleep(int.MaxValue);
					}
				}
				catch(Exception ex) {
					System.Windows.Forms.MessageBox.Show(ex.ToString());
				}

				//FileStream f = new FileStream(a as string, FileMode.Open);
				//f.Lock(0, f.Length);
				//while (true) {
				//Thread.Sleep(10000);
				//}

				//object l = new object();
				//bool f1 = true;
				//FileStream f;
				//while (true) {
				//	lock (l) {
				//		if (f1) {
				//			f1 = !f1;
				//			f = File.Open(@"d:\1.txt", FileMode.Open);
				//		}
				//	}
				//}
			});

			t.Start(filePath);
			threads.Add(t);
		}

		public void AddFile(string filePath) {
			if (Properties.Settings.Default.Files.Contains(filePath))
				return;
			Properties.Settings.Default.Files.Add(filePath);
			Properties.Settings.Default.Save();
			_AddFile(filePath);
		}

	}
}
