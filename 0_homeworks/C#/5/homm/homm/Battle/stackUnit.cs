using System;

namespace homm {
	class StackUnit {
		public Title title { get; private set; }
		public string name { get; private set; }

		public byte atk { get; private set; }
		public byte def { get; private set; }
		public byte speed { get; private set; }

		public sbyte luck { get; private set; }
		public sbyte morale { get; private set; }

		public DMG dmg { get; private set; }

		public byte hp { get; private set; }
		public byte lashUnitHp { get; private set; }

		public short number { get; private set; }

		public byte atkRange { get; private set; }

		bool isFlying;

		public Coord pos;

		public StackUnit(string Name, Title Title, byte Atk, byte Def, DMG Dmg, byte Speed, byte Hp, short Number = 1, byte AtkRange = 1, bool IsFlying = false, sbyte Luck = 0, sbyte Morale = 0) {
			name = Name;
			title = Title;

			atk = Atk;
			def = Def;
			dmg = Dmg;
			speed = Speed;
			lashUnitHp = hp = Hp;
			atkRange = AtkRange;
			isFlying = IsFlying;

			luck = Luck;
			morale = Morale;

			pos.y = -1;
			pos.x = -1;
			number = Number;
		}

		public double GetLuckBonus(Hero hero) {
			sbyte luck = (sbyte)(this.luck + hero.luck);
			if(luck == 0)
				return 1.0;

			double chance = 0;
			if (luck > 0) {
				if (luck >= 3)
					chance = 12.5;
				else if (luck == 2)
					chance = 8.3;
				else if (luck == 1)
					chance = 4.2;
				if(chance <= SingleRandom.Rand(1, 10000) / 100.0)
					return 2.0;
			}

			if (luck > 0) {
				if (luck <= -3)
					chance = 25;
				else if (luck == -2)
					chance = 16.6;
				else if (luck == -1)
					chance = 8.3;
				if (chance <= SingleRandom.Rand(1, 10000) / 100.0)
					return 0.5;
			}

			return 1.0;
		}

		public void PrintUnitInfo(Coord pos) {
			Console.ForegroundColor = ConsoleColor.White;
			Console.BackgroundColor = ConsoleColor.Black;

			Console.SetCursorPosition(pos.x, pos.y);
			if(isFlying)
				Console.Write($"{name,-10} {number,-4} Flying");
			else
				Console.Write($"{name,-10} {number,-4}       ");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Atk:   {atk}  ");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Def:   {def}  ");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Speed: {speed}  ");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Hp:    {hp} ({lashUnitHp})     ");
			Console.SetCursorPosition(pos.x, ++pos.y);
			Console.Write($"Dmg:   {dmg.min} - {dmg.max} ({atkRange})    ");
		}

		public void ColorBeforeMove() {
			Console.SetCursorPosition(38 + pos.x * 5, 2 + pos.y * 3);
			Console.Write('>');
			Console.SetCursorPosition(40 + pos.x * 5, 2 + pos.y * 3);
			Console.Write('<');
		}

		public void ClearColorBeforeMove(ref BattleMap map) {
			Console.SetCursorPosition(38 + pos.x * 5, 2 + pos.y * 3);
			map.GetLandscape(pos.x * 5 == 0 ? 0 : pos.x * 5 - 1, pos.y * 3).Print();
			Console.SetCursorPosition(40 + pos.x * 5, 2 + pos.y * 3);
			map.GetLandscape(pos.x * 5 + 1, pos.y * 3).Print();

			Console.SetCursorPosition(38 + pos.x * 5, 3 + pos.y * 3);
			map.GetLandscape(pos.x * 5 == 0 ? 0 : pos.x * 5 - 1, pos.y * 3 + 1).Print();
			Console.SetCursorPosition(39 + pos.x * 5, 3 + pos.y * 3);
			map.GetLandscape(pos.x * 5, pos.y * 3 + 1).Print();
			Console.SetCursorPosition(40 + pos.x * 5, 3 + pos.y * 3);
			map.GetLandscape(pos.x * 5 + 1, pos.y * 3 + 1).Print();
			Console.SetCursorPosition(41 + pos.x * 5, 3 + pos.y * 3);
			map.GetLandscape(pos.x * 5 + 2, pos.y * 3 + 1).Print();
		}

		public bool Move(Coord movePos, ref BattleMap map) {
			if(Math.Pow((movePos.x - pos.x),2) + Math.Pow((movePos.y - pos.y), 2) <= Math.Pow(speed, 2)) {
				Console.SetCursorPosition(39 + pos.x * 5, 2 + pos.y * 3);
				map.GetLandscape(pos.x * 5, pos.y * 3).Print();
				Console.SetCursorPosition(39 + pos.x * 5, 2 + pos.y * 3);
				Console.Write('_');

				Console.SetCursorPosition(40 + pos.x * 5, 2 + pos.y * 3);
				map.GetLandscape(pos.x * 5 + 1, pos.y * 3).Print();
				Console.SetCursorPosition(38 + pos.x * 5, 2 + pos.y * 3);
				map.GetLandscape(pos.x * 5 == 0 ? 0 : pos.x * 5 - 1, pos.y * 3).Print();


				Console.SetCursorPosition(38 + pos.x * 5, 3 + pos.y * 3);
				map.GetLandscape(pos.x * 5==0? 0 : pos.x * 5 - 1, pos.y * 3 + 1).Print();
				Console.SetCursorPosition(39 + pos.x * 5, 3 + pos.y * 3);
				map.GetLandscape(pos.x * 5, pos.y * 3 + 1).Print();
				Console.SetCursorPosition(40 + pos.x * 5, 3 + pos.y * 3);
				map.GetLandscape(pos.x * 5 + 1, pos.y * 3 + 1).Print();
				Console.SetCursorPosition(41 + pos.x * 5, 3 + pos.y * 3);
				map.GetLandscape(pos.x * 5 + 2, pos.y * 3 + 1).Print();

				pos = movePos;
				return true;
			}
			return false;
		}

		public UnitAttack? Attack(Coord attackPos) {
			if (Math.Pow((attackPos.x - pos.x), 2) + Math.Pow((attackPos.y - pos.y), 2) <= Math.Pow(atkRange, 2)) 
			//if (attackPos.x - pos.x + attackPos.y - pos.y <= atkRange) 
				return new UnitAttack((short)SingleRandom.Rand(dmg.min * number, dmg.max * number), atk);
			return null;
		}

		double GetAtkDefFactor(short diff) {
			if (diff > 0)
				return  (diff * 5 > 400 ? 400 : diff * 5) / 100.0 + 1;
			if (diff < 0)
				return  (diff * 3 < 30 ? 30 : diff * 3) / 100.0 + 1;
			return 1.00;
		}

		public void GetAttack(UnitAttack takedDmg, Hero hero) {
			int dmg = (int) Math.Round( takedDmg.physicalDmg * GetAtkDefFactor((short)(takedDmg.attack - this.def - hero.def)) );
			number -= (short)( dmg / hp );
			dmg %= hp;
			if (lashUnitHp > dmg)
				lashUnitHp -= (byte)dmg;
			else {
				--number;
				lashUnitHp = (byte)(lashUnitHp + hp - dmg);
			}
		}

	}
}
