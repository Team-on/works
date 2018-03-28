using System;

namespace homm {
	partial class BattleModule {
		void InitScreen() {
			Console.Clear();
			Console.ForegroundColor = ConsoleColor.Blue;
			Console.BackgroundColor = ConsoleColor.Black;

			for (byte i = 0; i < 47; ++i) {
				Console.SetCursorPosition(113, i);
				Console.Write('|');
				Console.SetCursorPosition(32, i);
				Console.Write('|');
			}
			for (byte i = 0; i < 32; ++i) {
				Console.SetCursorPosition(i, 9);
				Console.Write('_');
				if (i + 115 < Console.WindowWidth) {
					Console.SetCursorPosition(i + 114, 9);
					Console.Write('_');
				}
			}

			Console.SetCursorPosition(33, 38);
			for (byte i = 33; i < 113; ++i) {
				Console.Write('_');
			}

			Console.SetCursorPosition(87, 42);
			for (byte i = 87; i < 113; ++i) {
				Console.Write('_');
			}

			for (byte i = 39; i < 47; ++i) {
				//87  + 13 + 13
				Console.SetCursorPosition(87, i);
				Console.Write('|');
				Console.SetCursorPosition(100, i);
				Console.Write('|');
			}
			Console.SetCursorPosition(100, 42);
			Console.Write('+');


			PrintHeroInfo();
			PrintMapWithCell();
			arrow.PrintControllArrows();
		}

		void PrintMapWithCell() {
			map.Print(mapPrintPos);
			int x = 39, y = 2;
			Console.SetCursorPosition(x, y);
			for (int i = 0; i < 11; ++i) {
				for (int j = 0; j < 15; ++j) {
					Console.Write('_');
					Console.SetCursorPosition(x += 5, y);
				}
				x = 39;
				Console.SetCursorPosition(x, y += 3);
			}
		}

		void PrintHeroInfo() {
			pl.hero.PrintHeroInfo(new Coord(1, 1));
			pr.hero.PrintHeroInfo(new Coord(115, 1));
		}

		void PrintChoosenUnitInfo() {
			Coord pos = arrow.pos;
			StackUnit toPrint = pl.GetUnit(pos);
			if(toPrint != null) {
				toPrint.PrintUnitInfo(new Coord(1, 11));
				return;
			}

			toPrint = pr.GetUnit(pos);
			if (toPrint == null)
				return;
			toPrint.PrintUnitInfo(new Coord(115, 11));
		}
	}
}
