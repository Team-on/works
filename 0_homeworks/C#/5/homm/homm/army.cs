using System;

namespace homm {
	class Army {
		public Hero hero { private set; get; }
		StackUnit[] units;

		public Army(ref Hero newHero) {
			hero = newHero;
			units = new StackUnit[7];
			for (byte i = 0; i < units.Length; ++i)
				units[i] = null;
		}

		public bool AddUnit(StackUnit unit) {
			for (byte i = 0; i < units.Length; ++i)
				if (units[i] == null) {
					unit.pos.x = 0;
					switch (i) {
						case 0:
							unit.pos.y = 0;
							break;
						case 1:
							unit.pos.y = 2;
							break;
						case 2:
							unit.pos.y = 4;
							break;
						case 3:
							unit.pos.y = 5;
							break;
						case 4:
							unit.pos.y = 6;
							break;
						case 5:
							unit.pos.y = 8;
							break;
						case 6:
							unit.pos.y = 10;
							break;
					}
					units[i] = unit;
					return true;
				}
			return false;
		}

		public void SetUnitsPosX(short x) {
			for (byte i = 0; i < units.Length; ++i)
				if (units[i] != null) {
					units[i].pos.x = x;
				}
		}

		public void PrintUnits() {
			for (byte i = 0; i < units.Length; ++i)
				if (units[i] != null) {
					int x = 39 + units[i].pos.x * 5, y = 2 + units[i].pos.y * 3;
					Console.SetCursorPosition(x, y);
					units[i].title.Print();
					if (units[i].number < 10)
						Console.SetCursorPosition(x, y + 1);
					else
						Console.SetCursorPosition(x - 1, y + 1);

					Console.ForegroundColor = ConsoleColor.White;
					Console.BackgroundColor = ConsoleColor.Black;
					Console.Write(units[i].number);
				}
		}
	}
}
