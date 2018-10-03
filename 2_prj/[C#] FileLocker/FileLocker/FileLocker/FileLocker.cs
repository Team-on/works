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
		List<bool> isWorking = new List<bool>();

		public FileLocker() {
			//Properties.Settings.Default.Files.Clear();
			//Properties.Settings.Default.Save();
			foreach (var i in Properties.Settings.Default.Files)
				_AddFile(i);
		}

		public void Unlock(int id) {
			if (isWorking[id]) {
				threads[id].Abort();
				isWorking[id] = false;
			}
		}

		public void UnlockAll() {
			for(int i = 0; i < threads.Count; ++i) {
				if (isWorking[i]) {
					threads[i].Abort();
					isWorking[i] = false;
				}
			}
		}

		public void Remove(int id) {
			Properties.Settings.Default.Files.RemoveAt(id);
			Properties.Settings.Default.Save();
			Unlock(id);
		}

		public void Lock(int id) {
			if (!isWorking[id]) {
				threads[id] = CreateThread(Properties.Settings.Default.Files[id]);
				threads[id].Start();
				isWorking[id] = true;
			}
		}

		public void LockAll() {
			for(ushort i = 0; i < threads.Count; ++i) {
				if (!isWorking[i]) {
					threads[i] = CreateThread(Properties.Settings.Default.Files[i]);
					threads[i].Start();
					isWorking[i] = true;
				}
			}
		}

		void _AddFile(string filePath) {
			Thread t = CreateThread(filePath);

			t.Start();
			threads.Add(t);
			isWorking.Add(true);
		}

		Thread CreateThread(string filePath) {
			return new Thread(() => {
				string path = filePath.Clone() as string;
				File.Open(path as string, FileMode.Open);
				while (true)
					Thread.Sleep(int.MaxValue);

			});
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
