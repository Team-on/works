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
		Dictionary<int, FileStream> files = new Dictionary<int, FileStream>();

		public FileLocker() {
			//Properties.Settings.Default.Files.Clear();
			//Properties.Settings.Default.Save();
			foreach (var i in Properties.Settings.Default.Files)
				_AddFile(i);
		}

		public void Unlock(int id) {
			if (isWorking[id]) {
                threads[id].Abort();
                if (files.ContainsKey(id))
                    files.First(a => a.Key == id).Value.Dispose();
				isWorking[id] = false;
			}
		}

		public void UnlockAll() {
			for(int i = 0; i < threads.Count; ++i) {
				if (isWorking[i]) {
                    threads[i].Abort();
                    if (files.ContainsKey(i))
                        files.First(a => a.Key == i).Value.Dispose();
					isWorking[i] = false;
				}
			}
		}

		public void Remove(int id) {
			Unlock(id);
            threads.RemoveAt(id);
            isWorking.RemoveAt(id);
            files.Remove(id);
            Properties.Settings.Default.Files.RemoveAt(id);
			Properties.Settings.Default.Save();
		}

		public void Lock(int id) {
			if (!isWorking[id]) {
				threads[id] = CreateThread(id, Properties.Settings.Default.Files[id]);
				threads[id].Start();
				isWorking[id] = true;
			}
		}

		public void LockAll() {
			for(ushort i = 0; i < threads.Count; ++i) {
				if (!isWorking[i]) {
					threads[i] = CreateThread(i, Properties.Settings.Default.Files[i]);
					threads[i].Start();
					isWorking[i] = true;
				}
			}
		}

		void _AddFile(string filePath) {
			Thread t = CreateThread(threads.Count, filePath);

			t.Start();
			threads.Add(t);
			isWorking.Add(true);
        }

		Thread CreateThread(int id, string filePath) {
			return new Thread(() => {
				string path = filePath.Clone() as string;
                if (files.ContainsKey(id)) {
                    files.First(a => a.Key == id).Value.Dispose();
                    files.Remove(id);
                }
                files.Add(id, File.Open(path as string, FileMode.Open));
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
