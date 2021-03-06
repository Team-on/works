﻿using System;
using System.Diagnostics;
using System.Threading;

namespace homm {
	partial class BattleModule {
		ConsoleKey ReadyForInput() {
			Console.ForegroundColor = ConsoleColor.Black;
			Console.SetCursorPosition(0, 0);
			return Console.ReadKey().Key;
		}

		bool IsEnemyAround(ref StackUnit unit) {
			Army enemy= GetEnemyPlayer();
			if (enemy.GetUnit(new Coord(unit.pos.x, unit.pos.y - 1)) != null ||
				enemy.GetUnit(new Coord(unit.pos.x, unit.pos.y + 1)) != null ||
				enemy.GetUnit(new Coord(unit.pos.x + 1, unit.pos.y)) != null ||
				enemy.GetUnit(new Coord(unit.pos.x - 1, unit.pos.y)) != null )
				return true;	 
			return false;
		}

		void PeekUnitGetInput(ref StackUnit choosenUnit) {
			ConsoleKey read;
			Coord? selectedCoord = null;
			bool endOfTurn = false;

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

			StackUnit currEnemyUnit = GetEnemyPlayer().GetUnit(selectedCoord.Value);
			choosenUnit.isAttackBack = true;
			if (currEnemyUnit == null) {
				endOfTurn = choosenUnit.Move(selectedCoord.Value, ref map);
				if (endOfTurn && IsEnemyAround(ref choosenUnit)) {
					PrintCurrState();
					choosenUnit.ColorBeforeMove();
					AttackAfterMove(ref choosenUnit);
				}
			}
			else {
				UnitAttack? dealedDmg = choosenUnit.Attack(selectedCoord.Value);
				if (dealedDmg.HasValue) {
					endOfTurn = true;
					currEnemyUnit.GetAttack(
						new UnitAttack((short)(dealedDmg.Value.physicalDmg * choosenUnit.GetLuckBonus(currPlayer.hero)),
						(byte)(dealedDmg.Value.attack + currPlayer.hero.atk)),
						GetEnemyPlayer().hero
					);
					if (currEnemyUnit.isAttackBack && currEnemyUnit.IsAlive()) {
						dealedDmg = currEnemyUnit.Attack(choosenUnit.pos);
						choosenUnit.GetAttack(
							new UnitAttack((short)(dealedDmg.Value.physicalDmg * currEnemyUnit.GetLuckBonus(GetEnemyPlayer().hero)),
							(byte)(dealedDmg.Value.attack + GetEnemyPlayer().hero.atk)),
							currPlayer.hero
						);
						SingleLogBattle.log.LogAddToLine(" (Back)");
						currEnemyUnit.isAttackBack = false;
					}
					currEnemyUnit.ClearColorBeforeMove(ref map);
				}
			}

			if (endOfTurn)
				ChangePlayer();

EXIT_WITHOUT_MOVE:
			choosenUnit.ClearColorBeforeMove(ref map);
		}

		void AttackAfterMove(ref StackUnit choosenUnit) {
			ConsoleKey read;
			Coord? selectedCoord = null;

			do {
				read = 0;
				Console.SetCursorPosition(arrow.pos.x * 5 + 39, arrow.pos.y * 3 + 2);
				if (Console.KeyAvailable)
					read = ReadyForInput();

				if (read != 0) {
					if (read == ConsoleKey.Escape)
						return;
					selectedCoord = arrow.ControlArrows(read);
					arrow.PrintControllArrows();
				}
				Thread.Sleep(1);
			} while (selectedCoord == null);


			StackUnit currEnemyUnit = GetEnemyPlayer().GetUnit(selectedCoord.Value);
			if (currEnemyUnit != null){
				UnitAttack? dealedDmg = choosenUnit.Attack(selectedCoord.Value);
				if (dealedDmg.HasValue) {
					currEnemyUnit.GetAttack(
						new UnitAttack((short)(dealedDmg.Value.physicalDmg * choosenUnit.GetLuckBonus(currPlayer.hero)),
						(byte)(dealedDmg.Value.attack + currPlayer.hero.atk)),
						GetEnemyPlayer().hero
					);

					if (currEnemyUnit.isAttackBack && currEnemyUnit.IsAlive()) {
						dealedDmg = currEnemyUnit.Attack(choosenUnit.pos);
						choosenUnit.GetAttack(
							new UnitAttack((short)(dealedDmg.Value.physicalDmg * currEnemyUnit.GetLuckBonus(GetEnemyPlayer().hero)),
							(byte)(dealedDmg.Value.attack + GetEnemyPlayer().hero.atk)),
							currPlayer.hero
						);
						SingleLogBattle.log.LogAddToLine(" (Back)");
						currEnemyUnit.isAttackBack = false;
					}

					currEnemyUnit.ClearColorBeforeMove(ref map);
				}
			}
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
