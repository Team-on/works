using System;


namespace homm {
	partial class BattleModule {
		bool isRunning;
		Coord mapPrintPos;
		BattleMap map;

		Army pl, pr, currPlayer;

		ArrowBattle arrow;

		public ref Army Play() {
			SingleLogBattle.log.LogNewLine("Battle started " + pl.hero.name + " vs " + pr.hero.name);
			InitScreen();
			PrintCurrState();

			while (isRunning) {
				GetPlayerInput();
				CheckWin();
				PrintCurrState();
			}

			//end
			BeforeExit();
			Console.ForegroundColor = ConsoleColor.White;
			Console.SetCursorPosition(0, 46);
			SingleLogBattle.log.Clear();
			return ref (pr.IsArmyDie() ? ref pl : ref pr);
		}

		void CheckWin() {
			if (pr.IsArmyDie()) {
				SingleLogBattle.log.LogNewLine(pl.hero.name + " win!");
				isRunning = false;
				return;
			}
			if (pl.IsArmyDie()) {
				SingleLogBattle.log.LogNewLine(pr.hero.name + " win!");
				isRunning = false;
				return;
			}
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
