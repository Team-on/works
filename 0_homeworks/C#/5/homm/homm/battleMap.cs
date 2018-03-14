using System;

namespace homm {
	class Title {
		public ConsoleColor fore, back;
		public char symbol;

		public Title() {
			fore = ConsoleColor.Gray;
			back = ConsoleColor.Black;
			symbol = ' ';
		}

		public Title(char Symbol = ' ', ConsoleColor Fore = ConsoleColor.Gray, ConsoleColor Back = ConsoleColor.Black){
			fore = Fore;
			back = Back;
			symbol = Symbol;
		}

		public void Print() {
			if (Console.ForegroundColor != fore)
				Console.ForegroundColor = fore;
			if (Console.BackgroundColor != back)
				Console.BackgroundColor = back;
			Console.Write(symbol);
		}
	}

	class BattleMap {
		Title[,] landscape;

		public BattleMap() {
			landscape = new Title[34, 75];
			for (byte i = 0; i < landscape.GetLength(0); ++i)
				for (byte j = 0; j < landscape.GetLength(1); ++j)
					landscape[i, j] = new Title();
		}

		public enum LandscapeTypes : byte {FOREST, DESERT, NECROLANDS};
		public void GenerateLandscape(LandscapeTypes type) {
			ConsoleColor color = type == LandscapeTypes.FOREST     ? ConsoleColor.DarkGreen :
								 type == LandscapeTypes.DESERT     ? ConsoleColor.DarkYellow :
								 type == LandscapeTypes.NECROLANDS ? ConsoleColor.DarkGray :
																	 ConsoleColor.Black;
			for (byte i = 0; i < landscape.GetLength(0); ++i)
				for (byte j = 0; j < landscape.GetLength(1); ++j)
					landscape[i, j].back = color;
		}

		public void Print(Coord start) {
			Console.SetCursorPosition(start.x, start.y);
			for (byte i = 0; i < landscape.GetLength(0); ++i) {
				for (byte j = 0; j < landscape.GetLength(1); ++j)
					landscape[i, j].Print();
				Console.SetCursorPosition(start.x, ++start.y);
			}
		}
	}
}
