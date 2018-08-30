using System;

namespace ConsoleOOPMenu {
	public class MenuItem {
		public string PreText { get; set; }
		public string Text { get; set; }
		public string InBrakesText { get; set; }

		public ConsoleColor PreTextColor { get; set; }
		public ConsoleColor TextColor { get; set; }
		public ConsoleColor InBrakesTextColor { get; set; }

		public MenuItem() {
			PreTextColor = TextColor = InBrakesTextColor = ConsoleColor.Gray;
			PreText = Text = InBrakesText = "";
		}

		public void Print() {
			var prev = Console.ForegroundColor;

			if(PreText.Length != 0) {
				Console.ForegroundColor = PreTextColor;
				Console.Write($"{PreText} ");
			}

			Console.ForegroundColor = TextColor;
			Console.Write($"{Text}");

			if(InBrakesText.Length != 0) {
				Console.ForegroundColor = InBrakesTextColor;
				Console.Write($" ({InBrakesText})");
			}

			Console.ForegroundColor = prev;

		}
	}
}
