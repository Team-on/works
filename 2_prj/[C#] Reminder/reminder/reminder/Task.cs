using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;

namespace reminder{
    class Task{
		public DateTime dateTime;
		public string name, theme, description;
		public Image image;

		public Task(DateTime dateTime, string name, string theme, string description, Image image) {
			this.dateTime = dateTime;
			this.name = name;
			this.theme = theme;
			this.description = description;
			this.image = image;
		}


	}
}
