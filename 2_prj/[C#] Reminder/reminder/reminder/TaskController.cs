using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace reminder{
    class TaskController{
		static public System.Windows.Controls.Image defaultImage = new System.Windows.Controls.Image() { Source = new System.Windows.Media.Imaging.BitmapImage(new Uri(@"img\def.jpg", UriKind.Relative)) };
		List<Task> tasks;

		public TaskController() {
			tasks = new List<Task>();
		}

		public List<Task> GetTasksEnumerator() => tasks;

		public void AddTask(Task task) => tasks.Add(task);
		
		public void SortByTime() {
			tasks.Sort((a, b) => b.dateTime.CompareTo(a.dateTime));
		}

		public void Save() { }
		public void Load() { }
	}
}
