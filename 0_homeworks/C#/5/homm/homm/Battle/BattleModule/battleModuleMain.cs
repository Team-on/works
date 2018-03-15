using System;


namespace homm {
	partial class BattleModule {
		bool isRunning;
		Coord mapPrintPos;
		BattleMap map;

		Army pl, pr, currPlayer;

		ArrowBattle arrow;

		public void Play() {
			InitScreen();
			PrintCurrState();

			while (isRunning) {
				GetPlayerInput();
				PrintCurrState();
			}

			//end
			BeforeExit();
			Console.ForegroundColor = ConsoleColor.Magenta;
			Console.SetCursorPosition(0, 46);
		}

		void PrintCurrState() {
			pl.PrintUnits();
			pr.PrintUnits();
			PrintChoosenUnitInfo();
		}
	}
}
