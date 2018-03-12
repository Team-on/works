using System;

namespace homm {
	class GameTitle {
		public ConsoleColor fore, back;
		public char symbol;
		public StackUnit currUnit;

		public GameTitle() {
			fore = ConsoleColor.Gray;
			back = ConsoleColor.Black;
			symbol = ' ';
			currUnit = null;
		}

		public void Print() {
			if (Console.ForegroundColor != fore)
				Console.ForegroundColor = fore;
			if (Console.BackgroundColor != back)
				Console.BackgroundColor = back;
			if (currUnit == null)
				Console.Write(symbol);
			else
				Console.Write(currUnit.title.symbol);
		}
	}

	class BattleMap {
		GameTitle[,] map;

		void GenerateLandscape() {
			for (byte i = 0; i < map.GetLength(0); ++i)
				for (byte j = 0; j < map.GetLength(1); ++j) {
					map[i, j].symbol = '-';
					//map[i, j].back = ConsoleColor.DarkYellow;
				}
		}

		public BattleMap() {
			map = new GameTitle[11, 15];
			for (byte i = 0; i < map.GetLength(0); ++i)
				for (byte j = 0; j < map.GetLength(1); ++j)
					map[i, j] = new GameTitle();
			GenerateLandscape();
		}

		void RemoveUnit(Coord pos) {
			map[pos.y, pos.x].currUnit = null;
		}

		void SetUnit(Coord pos, ref StackUnit unit) {
			map[pos.y, pos.x].currUnit = unit;
		}

		public void Print(Coord start) {
			Console.CursorLeft = start.x;
			Console.CursorTop = start.y;
			for (byte i = 0; i < map.GetLength(0); ++i) {
				for (byte j = 0; j < map.GetLength(1); ++j) {
					Console.Write(' ');
					map[i, j].Print();
					Console.Write(' ');
				}
				start.y += 2;
				Console.CursorLeft = start.x;
				Console.CursorTop  = start.y;
			}
		}
	}
}
