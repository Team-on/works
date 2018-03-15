using System;
using System.Diagnostics;
using System.Threading;

namespace homm {
	partial class BattleModule {
		ConsoleKey ReadyForInput() {
			Console.ForegroundColor = ConsoleColor.Black;
			Console.SetCursorPosition(0, 0);
			return Console.ReadKey().Key;
		}

		void PeekUnitGetInput(ref StackUnit choosenUnit) {
			ConsoleKey read;
			Coord? selectedCoord = null;
			bool endOfTurn = false, exitWithoutMove = false;

			choosenUnit.ColorBeforeMove();

			do {
				read = 0;
				Console.SetCursorPosition(arrow.pos.x * 5 + 39, arrow.pos.y * 3 + 2);
				if (Console.KeyAvailable)
					read = ReadyForInput();

				if (read != 0) {
					if (read == ConsoleKey.Escape)
						goto EXIT_WITHOUT_MOVE;
					selectedCoord = arrow.ControlArrows(read);
					arrow.PrintControllArrows();
				}
				Thread.Sleep(1);
			} while (selectedCoord == null);

			if (currPlayer.GetUnit(arrow.pos) != null)
				goto EXIT_WITHOUT_MOVE;

			if (GetEnemyPlayer().GetUnit(selectedCoord.Value) == null)
				endOfTurn = choosenUnit.Move(selectedCoord.Value, ref map);
			else {
				UnitAttack? dealedDmg =  choosenUnit.Attack(selectedCoord.Value);
				Console.Write("Attack {0}  ", dealedDmg.HasValue);
				if (dealedDmg.HasValue) {
					endOfTurn = true;
					GetEnemyPlayer().GetUnit(selectedCoord.Value).GetAttack( 
						new UnitAttack((short)(dealedDmg.Value.physicalDmg * choosenUnit.GetLuckBonus(currPlayer.hero)),
						(byte)(dealedDmg.Value.attack + currPlayer.hero.atk)),
						GetEnemyPlayer().hero
					);
					GetEnemyPlayer().GetUnit(selectedCoord.Value).ClearColorBeforeMove(ref map);
				}
			}

			if (endOfTurn)
				ChangePlayer();

EXIT_WITHOUT_MOVE:
			choosenUnit.ClearColorBeforeMove(ref map);
		}

		void GetPlayerInput() {
			Console.SetCursorPosition(arrow.pos.x * 5 + 39, arrow.pos.y * 3 + 2);

			ConsoleKey read = 0;
			while (read == 0) {
				if (Console.KeyAvailable)
					read = ReadyForInput();
				Thread.Sleep(1);
			}

			if (read == ConsoleKey.Enter || read == ConsoleKey.RightArrow || read == ConsoleKey.UpArrow || read == ConsoleKey.DownArrow || read == ConsoleKey.LeftArrow) {
				if (read != ConsoleKey.Enter) {
					arrow.ControlArrows(read);
					arrow.PrintControllArrows();
					return;
				}

				Coord? selectedCoord = arrow.ControlArrows(read);
				arrow.PrintControllArrows();

				if (selectedCoord.HasValue) {
					StackUnit choosenUnit = currPlayer.GetUnit(selectedCoord.Value);
					if (choosenUnit != null)
						PeekUnitGetInput(ref choosenUnit);
				}

			}

			else if (read == ConsoleKey.Escape)
				isRunning = false;
		}
	}
}
