using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace homm {
	class Hero {
		public Title title { get; private set; }
		public string name { get; private set; }

		public byte atk, def, moral, luck;

		public Hero(Title Title, string Name) { title = Title; name = Name; }

		public void PrintHeroInfo(Coord pos) {
			Console.ForegroundColor = ConsoleColor.White;
			Console.BackgroundColor = ConsoleColor.Black;

			Console.SetCursorPosition(pos.x, pos.y);
			Console.Write($"{name,-14} Lvl: 1");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Atk:   {atk}");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Def:   {def}");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Moral: {moral}");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Luck:  {luck}");
		}
	}
}
