using System;

namespace homm {
	partial class BattleModule {
		Coord mapPrintPos;
		BattleMap map;
		Army pl, pr;

		Coord ArrowPos = new Coord(0, 0);
		Coord ControlArrows(ConsoleKey read) {
				if (read == ConsoleKey.LeftArrow)
					--ArrowPos.x;
				else if (read == ConsoleKey.RightArrow)
					++ArrowPos.x;
				else if (read == ConsoleKey.UpArrow)
					--ArrowPos.y;
				else if (read == ConsoleKey.DownArrow)
					++ArrowPos.y;
				else if (read == ConsoleKey.Enter)
					return ArrowPos;

				if (ArrowPos.x == -1)
					ArrowPos.x = 14;
				else if (ArrowPos.x == 15)
					ArrowPos.x = 0;
				if (ArrowPos.y == -1)
					ArrowPos.y = 10;
				else if (ArrowPos.y == 11)
					ArrowPos.y = 0;

			return new Coord(-1,-1);
		}

		void PrintControllArrows() {
			Console.BackgroundColor = ConsoleColor.Black;
			Console.ForegroundColor = ConsoleColor.White;
			int x, y;
			x = 39; y = 36;
			Console.SetCursorPosition(x, y);
			for (int j = 0; j < 15; ++j) {
				if (ArrowPos.x == j) {
					Console.Write('^');
					Console.SetCursorPosition(x - 1, y + 1);
					Console.Write(@"/@\");
				}
				else {
					Console.Write(' ');
					Console.SetCursorPosition(x - 1, y + 1);
					Console.Write("   ");
				}
				Console.SetCursorPosition(x += 5, y);
			}
			x = 35; y = 2;
			Console.SetCursorPosition(x, y);
			for (int i = 0; i < 11; ++i) {
				if (ArrowPos.y == i) {
					Console.Write('>');
					Console.SetCursorPosition(x - 1, y - 1);
					Console.Write('-');
					Console.SetCursorPosition(x - 1, y);
					Console.Write('@');
					Console.SetCursorPosition(x - 1, y + 1);
					Console.Write('-');
				}
				else {
					Console.Write(' ');
					Console.SetCursorPosition(x - 1, y - 1);
					Console.Write(' ');
					Console.SetCursorPosition(x - 1, y);
					Console.Write(' ');
					Console.SetCursorPosition(x - 1, y + 1);
					Console.Write(' ');
				}
				Console.SetCursorPosition(x, y += 3);
			}
		}

		void GetPlayerInput() {
			Console.SetCursorPosition(0, 0);
			Console.ForegroundColor = ConsoleColor.Black;
			ConsoleKey read = Console.ReadKey().Key;

			if (read == ConsoleKey.Enter || read == ConsoleKey.RightArrow || read == ConsoleKey.UpArrow || read == ConsoleKey.DownArrow || read == ConsoleKey.LeftArrow) {
				ControlArrows(read);
				PrintControllArrows();
			}

			if (read == ConsoleKey.Escape)
				Environment.Exit(0);
		}

		public void Play() {
			InitScreen();
			PrintControllArrows();
			PrintCurrState();


			while (true) {
				GetPlayerInput();
				PrintCurrState();
			}

			//end
			BeforeExit();
			Console.ForegroundColor = ConsoleColor.Magenta; 
			Console.SetCursorPosition(0, 46);
		}

		void PrintCurrState() {
			//PrintMapWithCell();
			pl.PrintUnits();
			pr.PrintUnits();
		}
	}
}
