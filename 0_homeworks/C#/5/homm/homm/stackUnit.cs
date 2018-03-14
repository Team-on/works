using System;

namespace homm {
	class StackUnit {
		public Title title { get; private set; }
		public string name { get; private set; }

		public byte atk { get; private set; }
		public byte def { get; private set; }
		public byte speed { get; private set; }

		public DMG dmg { get; private set; }

		public byte hp { get; private set; }
		public byte lashUnitHp { get; private set; }

		public short number { get; private set; }

		public byte atkRange { get; private set; }

		bool isFlying;

		public Coord pos;

		public StackUnit(string Name, Title Title, byte Atk, byte Def, DMG Dmg, byte Speed, byte Hp, short Number = 1, byte AtkRange = 1, bool IsFlying = false) {
			name = Name;
			title = Title;

			atk = Atk;
			def = Def;
			dmg = Dmg;
			speed = Speed;
			lashUnitHp = hp = Hp;
			atkRange = AtkRange;
			isFlying = IsFlying;

			pos.y = -1;
			pos.x = -1;
			number = Number;
		}

		void Move() {

		}

	}
}
