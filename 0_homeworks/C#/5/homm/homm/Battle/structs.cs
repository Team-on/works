namespace homm {

	static class SingleRandom {
		static System.Random rnd;

		static SingleRandom() {
			rnd = new System.Random();
		}

		/// <summary>
		///[min, max]
		/// </summary>
		public static int Rand(int min, int max) {
			return rnd.Next(min, max + 1);
		}
	}

	struct Coord {
		public int x, y;
		public Coord(int X, int Y) { x = X; y = Y; }
	}

	struct DMG {
		public short max, min;
		public DMG(short Min, short Max) { max = Max; min = Min; }
	}

	struct UnitAttack{
		public short physicalDmg;
		public byte  attack;

		public UnitAttack(short PhysicalDmg, byte Attack) {
			physicalDmg = PhysicalDmg;
			attack = Attack;
		}
	}

	//struct Stat {
	//	public byte baseStat;
	//	public short heroBonus;
	//	short CurrValue;
	//	public short currValue {get { return CurrValue;}}

	//	public Stat(byte BaseStat, short HeroBonus = 0) {
	//		baseStat = BaseStat;
	//		heroBonus = HeroBonus;
	//		CurrValue = (short)(heroBonus + baseStat);
	//	}
		
	//	public void ChangeHeroBonus(short HeroBonus) {
	//		heroBonus = HeroBonus;
	//		CurrValue = (short)(heroBonus + baseStat);
	//	}
	//}
}
