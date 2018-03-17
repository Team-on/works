using System;


namespace homm {
	partial class BattleModule {
		bool isRunning;
		Coord mapPrintPos;
		BattleMap map;

		Army pl, pr, currPlayer;

		ArrowBattle arrow;

		public void Play() {
			SingleLogBattle.log.LogNewLine("Battle started " + pl.hero.name + " vs " + pr.hero.name);
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
			SingleLogBattle.log.Clear();
		}

		void PrintCurrState() {
			SingleLogBattle.log.PrintLog(new Coord(35, 40), 7, 50);
			pl.PrintUnits(false);
			pr.PrintUnits(false);
			pl.PrintUnits();
			pr.PrintUnits();
			PrintChoosenUnitInfo();
		}
	}
}
