using System;

namespace homm {
	partial class BattleModule {
		Coord mapPrintPos;
		BattleMap map;
		Army pl, pr;

		Army currPlayer;

		ArrowBattle arrow;

		public void Play() {
			InitScreen();
			PrintCurrState();

			while (IsRunning()) {
				GetPlayerInput();
				PrintCurrState();
			}

			//end
			BeforeExit();
			Console.ForegroundColor = ConsoleColor.Magenta;
			Console.SetCursorPosition(0, 46);
		}

		bool IsRunning() {
			return true;
		}

		void GetPlayerInput() {
			Console.SetCursorPosition(0, 0);
			Console.ForegroundColor = ConsoleColor.Black;
			ConsoleKey read = Console.ReadKey().Key;

			if (read == ConsoleKey.Enter || read == ConsoleKey.RightArrow || read == ConsoleKey.UpArrow || read == ConsoleKey.DownArrow || read == ConsoleKey.LeftArrow) {
				if (read != ConsoleKey.Enter) {
					arrow.ControlArrows(read);
					arrow.PrintControllArrows();
					return;
				}

				Coord? selectedUnit = arrow.ControlArrows(read);
				arrow.PrintControllArrows();

				if (selectedUnit != null) {
					StackUnit choosenUnit = currPlayer.GetUnit((Coord)(selectedUnit)); 
					//if (choosenUnit != null) {
					//	choosenUnit.PrintUnitInfo(new Coord(0, 0));
					//}
				}

			}

			if (read == ConsoleKey.Escape)
				Environment.Exit(0);
		}

		void PrintCurrState() {
			//PrintMapWithCell();
			pl.PrintUnits();
			pr.PrintUnits();
			PrintChoosenUnitInfo();
		}
	}
}
